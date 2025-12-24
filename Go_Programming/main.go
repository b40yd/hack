package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"sort"
	"strings"
	"sync"

	"github.com/google/gopacket"
	"github.com/google/gopacket/layers"
	"github.com/google/gopacket/pcap"
	"github.com/google/gopacket/tcpassembly"
	"github.com/google/gopacket/tcpassembly/tcpreader"
)

// --- 数据结构 ---

type HttpTransaction struct {
	ReqHeader string
	ReqBody   []byte
	ResHeader string
	IsSSE     bool
	SseChunks []string // 存储原始数据块（Chunks）而非行
	mu        sync.Mutex
}

var (
	sessionPool = make(map[string]*HttpTransaction)
	poolMu      sync.Mutex
)

func getFlowKey(netFlow, tcpFlow gopacket.Flow) string {
	endpoints := []string{
		fmt.Sprintf("%s:%s", netFlow.Src(), tcpFlow.Src()),
		fmt.Sprintf("%s:%s", netFlow.Dst(), tcpFlow.Dst()),
	}
	sort.Strings(endpoints)
	return strings.Join(endpoints, "|")
}

// --- TCP 重组引擎 ---

type httpStreamFactory struct{}

func (f *httpStreamFactory) New(netFlow, tcpFlow gopacket.Flow) tcpassembly.Stream {
	h := &httpStream{
		netFlow: netFlow,
		tcpFlow: tcpFlow,
		r:       tcpreader.NewReaderStream(),
	}
	go h.run()
	return &h.r
}

type httpStream struct {
	netFlow, tcpFlow gopacket.Flow
	r                tcpreader.ReaderStream
}

func (h *httpStream) run() {
	buf := bufio.NewReader(&h.r)
	key := getFlowKey(h.netFlow, h.tcpFlow)

	for {
		peek, err := buf.Peek(4)
		if err != nil {
			return
		}
		peekStr := string(peek)

		if isMethod(peekStr) {
			if req, err := http.ReadRequest(buf); err == nil {
				body, _ := io.ReadAll(req.Body)
				req.Body.Close()
				updateSession(key, func(tx *HttpTransaction) {
					tx.ReqHeader = formatFullRequest(req)
					tx.ReqBody = body
				})
				continue
			}
		} else if strings.HasPrefix(peekStr, "HTTP") {
			if res, err := http.ReadResponse(buf, nil); err == nil {
				handleResponse(key, res, buf)
				continue
			}
		}
		_, _ = buf.ReadByte()
	}
}

func isMethod(p string) bool {
	methods := []string{"GET ", "POST", "PUT ", "DELE", "HEAD", "OPTI", "PATC"}
	for _, m := range methods {
		if p == m { return true }
	}
	return false
}

// --- 渲染与 Chunk 重组逻辑 ---

func handleResponse(key string, res *http.Response, r *bufio.Reader) {
	isSSE := strings.Contains(strings.ToLower(res.Header.Get("Content-Type")), "text/event-stream")
	
	updateSession(key, func(tx *HttpTransaction) {
		tx.ResHeader = formatFullResponse(res)
		tx.IsSSE = isSSE
	})

	if isSSE {
		// SSE 块重组模式：不再按行读取，而是按缓冲区数据块读取
		tempBuf := make([]byte, 4096)
		for {
			n, err := r.Read(tempBuf) // 只要 TCP 层有数据推送到 Reader，这里就会返回
			if err != nil {
				break
			}
			chunk := string(tempBuf[:n])
			updateSession(key, func(tx *HttpTransaction) {
				tx.SseChunks = append(tx.SseChunks, chunk)
				renderSseTransaction(tx)
			})
		}
	} else {
		body, _ := io.ReadAll(res.Body)
		res.Body.Close()
		updateSession(key, func(tx *HttpTransaction) {
			renderNormalTransaction(tx, body)
		})
	}
}

func renderSseTransaction(tx *HttpTransaction) {
	// 聚合重绘：每次收到一个 TCP 载荷块，重新渲染
	fmt.Printf("\n\x1b[1;35m[SSE AGGREGATED VIEW - %d PAYLOAD CHUNKS]\x1b[0m\n", len(tx.SseChunks))
	fmt.Print(tx.ReqHeader)
	if len(tx.ReqBody) > 0 {
		fmt.Println("  \x1b[90m[Request Body]\x1b[0m")
		prettyJSON(string(tx.ReqBody), "    ")
	}
	fmt.Printf("\n%s\n", tx.ResHeader)
	
	fmt.Println("\x1b[1;33m[Stream Content History]\x1b[0m")
	// 这里按原样输出所有 Chunk，不做强制换行，保留原始传输格式
	for i, chunk := range tx.SseChunks {
		fmt.Printf("\x1b[90m--- Chunk %d (%d bytes) ---\x1b[0m\n", i, len(chunk))
		// 尝试对 Chunk 中的 data: 部分进行高亮渲染
		renderRawSseChunk(chunk)
	}
	fmt.Printf("\x1b[1;35m%s\x1b[0m\n", strings.Repeat("-", 60))
}

func renderRawSseChunk(chunk string) {
	lines := strings.Split(chunk, "\n")
	for _, line := range lines {
		trimmed := strings.TrimSpace(line)
		if strings.HasPrefix(trimmed, "data:") {
			content := strings.TrimSpace(strings.TrimPrefix(trimmed, "data:"))
			fmt.Printf("  \x1b[32mdata:\x1b[0m ")
			if !tryPrettyJSON(content, "    ") {
				fmt.Println(content)
			}
		} else {
			fmt.Println("  " + line)
		}
	}
}

func renderNormalTransaction(tx *HttpTransaction, body []byte) {
	fmt.Printf("\n\x1b[1;36m%s\x1b[0m\n", strings.Repeat("=", 60))
	fmt.Print(tx.ReqHeader)
	if len(tx.ReqBody) > 0 {
		fmt.Println("  \x1b[90m[Request Body]\x1b[0m")
		prettyJSON(string(tx.ReqBody), "    ")
	}
	fmt.Printf("\n%s", tx.ResHeader)
	if len(body) > 0 {
		fmt.Println("  \x1b[90m[Response Body]\x1b[0m")
		prettyJSON(string(body), "    ")
	}
	fmt.Printf("\x1b[1;36m%s\x1b[0m\n", strings.Repeat("=", 60))
}

// --- 辅助工具 ---

func formatFullRequest(req *http.Request) string {
	var b strings.Builder
	b.WriteString(fmt.Sprintf("\x1b[1;32m▶ %s %s %s\x1b[0m\n", req.Method, req.URL.RequestURI(), req.Proto))
	b.WriteString(fmt.Sprintf("\x1b[1;33mHost:\x1b[0m %s\n", req.Host))
	for k, v := range req.Header {
		b.WriteString(fmt.Sprintf("\x1b[1;33m%s:\x1b[0m %s\n", k, strings.Join(v, ", ")))
	}
	return b.String()
}

func formatFullResponse(res *http.Response) string {
	var b strings.Builder
	b.WriteString(fmt.Sprintf("\x1b[1;34m◀ %s %s\x1b[0m\n", res.Proto, res.Status))
	for k, v := range res.Header {
		b.WriteString(fmt.Sprintf("\x1b[1;33m%s:\x1b[0m %s\n", k, strings.Join(v, ", ")))
	}
	return b.String()
}

func tryPrettyJSON(content string, indent string) bool {
	var v interface{}
	if err := json.Unmarshal([]byte(content), &v); err == nil {
		p, _ := json.MarshalIndent(v, indent, "  ")
		fmt.Println(string(p))
		return true
	}
	return false
}

func prettyJSON(content string, indent string) {
	if !tryPrettyJSON(content, indent) {
		fmt.Printf("%s%s\n", indent, content)
	}
}

// --- 基础设施 ---

func updateSession(key string, fn func(*HttpTransaction)) {
	poolMu.Lock()
	tx, ok := sessionPool[key]
	if !ok {
		tx = &HttpTransaction{}
		sessionPool[key] = tx
	}
	poolMu.Unlock()
	tx.mu.Lock()
	defer tx.mu.Unlock()
	fn(tx)
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: sniffer file <path> | live -i <interface>")
		return
	}
	
	var path string
	if os.Args[1] == "file" {
		path = getPath(os.Args)
		if strings.HasPrefix(path, "~") {
			home, _ := os.UserHomeDir()
			path = filepath.Join(home, path[1:])
		}
		runEngine(path, "", true)
	} else if os.Args[1] == "live" {
		iface := "eth0"
		for i, a := range os.Args {
			if a == "-i" && i+1 < len(os.Args) { iface = os.Args[i+1] }
		}
		runEngine("", iface, false)
	}
}

func runEngine(file, iface string, isFile bool) {
	var handle *pcap.Handle
	var err error
	if isFile {
		handle, err = pcap.OpenOffline(file)
	} else {
		handle, err = pcap.OpenLive(iface, 65535, true, pcap.BlockForever)
	}
	if err != nil { log.Fatal(err) }
	defer handle.Close()

	_ = handle.SetBPFFilter("tcp")

	

	assembler := tcpassembly.NewAssembler(tcpassembly.NewStreamPool(&httpStreamFactory{}))
	packetSource := gopacket.NewPacketSource(handle, handle.LinkType())

	for packet := range packetSource.Packets() {
		if packet.TransportLayer() != nil && packet.TransportLayer().LayerType() == layers.LayerTypeTCP {
			tcp := packet.TransportLayer().(*layers.TCP)
			assembler.AssembleWithTimestamp(packet.NetworkLayer().NetworkFlow(), tcp, packet.Metadata().Timestamp)
		}
	}
	assembler.FlushAll()
}

func getPath(args []string) string {
	for i, a := range args {
		if (a == "--path" || a == "-p") && i+1 < len(args) { return args[i+1] }
	}
	if len(args) > 2 && !strings.HasPrefix(args[2], "-") { return args[2] }
	return ""
}
