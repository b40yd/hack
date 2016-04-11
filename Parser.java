package main;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class Parser {
	private StringBuffer response = new StringBuffer();
	private static byte crlf13 = (byte) 13;
	private static byte crlf10 = (byte) 10;
	private InputStream input;
	private OutputStream output;
	private Socket socket;
	public InputStream getInput() {
		return input;
	}

	public void setInput(InputStream input) {
		this.input = input;
	}

	public OutputStream getOutput() {
		return output;
	}

	public void setOutput(OutputStream outputStream) {
		this.output = outputStream;
	}

	public StringBuffer getResponse() {
		return response;
	}

	public void setResponse(StringBuffer response) {
		this.response = response;
	}
	public Parser createSocket(String host,int port){
		try {
			socket = new Socket(host, port);
			this.setInput(socket.getInputStream());
			this.setOutput(socket.getOutputStream());
			this.setSocket(socket);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return this;
	}
	
	public Socket getSocket() {
		return socket;
	}

	public void setSocket(Socket socket) {
		this.socket = socket;
	}

	public byte[] recvMsg() {

		byte[] crlf = new byte[1];
		ArrayList tmp = new ArrayList();
		int crlfNum = 0; // 已经连接的回车换行数 crlfNum=4为头部结束
		try {
			while (this.getInput().read(crlf) != -1) // 读取头部
			{
				if (crlf[0] == crlf13 || crlf[0] == crlf10) {
					crlfNum++;
				} else {
					crlfNum = 0;
				} // 不是则清
				response = response.append(new String(crlf, 0, 1)); // byte数组相加
				if (crlfNum == 4)
					break;
			}
			String tempStr = (new String(response)).toUpperCase();

			String ss1 = "CONTENT-LENGTH:";
			String ss2 = new String("TRANSFER-ENCODING: CHUNKED");
			int CONTENT_LENGTH = 0;
			boolean beChucked = false;

			int clIndex = tempStr.indexOf(ss1);
			int chuckIndex = tempStr.indexOf(ss2); // 为CHUNKED型
			byte requst[] = tempStr.getBytes();
			if (clIndex != -1) { // 从clIndex+1起至/r/n
				StringBuffer sb = new StringBuffer();

				for (int i = (clIndex + 16);; i++) {
					if (requst[i] != (byte) 13 && requst[i] != (byte) 10) {
						sb.append((char) requst[i]);
					} else
						break;
				}

				CONTENT_LENGTH = Integer.parseInt(sb.toString()); // 正式的HTML文件的大小
				// System.out.println("CONTENT_LENGTH== "+CONTENT_LENGTH);
			}
			if (chuckIndex != -1)
				beChucked = true;
			if (beChucked) // 为Chucked
			{
				int ChuckSize = 0;
				while ((ChuckSize = getChuckSize()) > 0) // 多个Chucked
				{
					tmp = readLenData(ChuckSize + 2);// 读取定长数据
				}
				tmp = readLenData(2); // 最后的2位
			}

			if (CONTENT_LENGTH > 0) {
				tmp = readLenData(CONTENT_LENGTH);// 读取定长数据
			}
			// System.out.println(request);

		} catch (IOException e) {
			System.out.println("Read Http Header Error!");
			// return null;
		}

		byte[] rs = new byte[tmp.size()];
		for (int n = 0; n < tmp.size(); n++) {
			rs[n] = (Byte) tmp.get(n);
		}

		return rs;
	}

	private ArrayList readLenData(int size) // 读取定长数据
	{
		ArrayList tmp = new ArrayList();
		int readed = 0; // 已经读取数
		try {
			int available = 0;// input.available(); //可读数
			if (available > (size - readed))
				available = size - readed;
			while (readed < size) {
				while (available == 0) { // 等到有数据可读
					available = this.getInput().available(); // 可读数
				}
				if (available > (size - readed))
					available = size - readed; // size-readed--剩余数
				if (available > 1024)
					available = 1024; // size-readed--剩余数
				byte[] buffer = new byte[available];
				int reading = this.getInput().read(buffer);
				response = response.append(new String(buffer, 0, reading));
				// tmp = tmp.append(new String(buffer, 0, reading)); // byte数组相加
				for (int n = 0; n < buffer.length; n++) {
					tmp.add(buffer[n]);
				}

				readed += reading; // 已读字符
			}
			// System.out.println("readed: "+readed);
			// return request;
		} catch (IOException e) {
			System.out.println("Read readLenData Error!");
		}
		return tmp;
	}

	private int getChuckSize() // Chuck大小
	{
		byte[] crlf = new byte[1];
		StringBuffer sb1 = new StringBuffer();
		int crlfNum = 0; // 已经连接的回车换行数 crlfNum=4为头部结束

		try {
			while (this.getInput().read(crlf) != -1) // 读取头部
			{
				if (crlf[0] == crlf13 || crlf[0] == crlf10) {
					crlfNum++;
				} else {
					crlfNum = 0;
				} // 不是则清
				sb1.append((char) crlf[0]);
				response = response.append(new String(crlf, 0, 1)); // byte数组相加
				if (crlfNum == 2)
					break;
			}
		} catch (IOException e) {
			System.out.println("Read Http Package Error!");
			return 0;
		}

		return Integer.parseInt((sb1.toString()).trim(), 16); // 16进控制
	}
}
