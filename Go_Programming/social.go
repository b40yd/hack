package main

import (
	"database/sql"
	_ "github.com/go-sql-driver/mysql"
	"log"
	"os"
	"bufio"
	"io"
	"fmt"
	"strings"
	"bytes"
	"encoding/base64"
)

type User struct {
	id			int
	name		string
	email 		string
	password	string
	salt		string
	fromSite	string
}

func insert(db *sql.DB, user *User) {
	stmt, err := db.Prepare("INSERT INTO user(username, email, password, salt, fromSite) VALUES(?, ?, ?, ?, ?)")
	defer stmt.Close()

	if err != nil {
		log.Println(err)
		return
	}
	_,e := stmt.Exec(user.name, user.email,user.password,user.salt,user.fromSite)
	if(e != nil){
		log.Println(e)
	}
	//stmt.Exec("test1", "test1@example.com","123","example.com","example.com")

}

func readData(db *sql.DB,fromSite string,file string){
	rw,err := os.Open(file)
    if err != nil {
        panic(err)
    }
    defer rw.Close()
    rb := bufio.NewReader(rw)
    user := &User{}
    var i int = 0
    var insertSQL string = "INSERT INTO user(id, username, email, password, salt, fromSite) VALUES";
    var buffer bytes.Buffer
    buffer.WriteString(insertSQL)
    for {
        line, _, err := rb.ReadLine()
        if err == io.EOF {
            break
        }
        //fmt.Println(string(line))
        splitLine := strings.Split(string(line),",")
        if i <=1000000 || len(splitLine) < 3 {
        	i++
        	continue
        }
        //do something
        if strings.ToUpper(fromSite) == "QQ" {
        	user.name = strings.Replace(splitLine[0], "\\", "\\\\", -1)
	        user.email = strings.Replace(splitLine[2], "\\", "\\\\", -1)
	        user.password = strings.Replace(splitLine[1], "\\", "\\\\", -1)
	        if len(splitLine) > 4{     	
	        	if user.name != "" || user.password != "" {
	        		user.salt = strings.Replace(splitLine[4], "\\", "\\\\", -1)
	        		user.fromSite = strings.Replace(splitLine[3], "\\", "\\\\", -1)
	        	}
	        }

        }else if strings.ToUpper(fromSite) == "TIANYA"{
        	user.name = strings.Replace(splitLine[2], "\\", "\\\\", -1)
	        user.email = strings.Replace(splitLine[3], "\\", "\\\\", -1)
	        user.password = strings.Replace(splitLine[7], "\\", "\\\\", -1)
	        if len(splitLine) > 4{     	
	        	if user.name != "" || user.password != "" {
	        		// user.salt = strings.Replace(splitLine[4], "\\", "\\\\", -1)
	        		user.fromSite = strings.Replace(splitLine[4], "\\", "\\\\", -1)
	        	}
	        }
        }
        
        
        if user.name == "" || user.password == "" {
        	continue
        }
        
        value := fmt.Sprintf("(\"%d\", \"%s\", \"%s\", \"%s\", \"%s\",\"%s\"),",i,user.name,user.email,base64.StdEncoding.EncodeToString([]byte(user.password)),user.salt,user.fromSite)
        
        buffer.WriteString(value)
        if i % 1000000 == 0 {
        	userFile := fmt.Sprintf("data/%d.sql",i)
        	fin,err := os.Create(userFile)
		    defer fin.Close()
		    if err != nil{
		        fmt.Println(userFile,err)
		        return

		    }
		    fin.WriteString(strings.Trim(buffer.String(),","))
        	buffer.Reset()
        	buffer.WriteString(insertSQL)
        	fmt.Println("当前行数-->%d", i)
        	break
        }
        i++
        //insert(db,user)
        
        // if i > 10 {
        // 	break
        // }
        
    }
}

func main() {
	db, err := sql.Open("mysql", "root:meiyoumima@/social_engineer")
	if err != nil {
		log.Fatalf("Open database error: %s\n", err)
	}
	defer db.Close()
	var fromSite string
	var file string
	err = db.Ping()
	help := "Exec Command Args[from site](tianya csdn QQ...) File.\r\nExample:\r\nsh> ./social tianya tianya_data.csv"
	if err != nil {
		log.Fatal(err)
	}
	if len(os.Args) > 1 {
		if os.Args[1] == "-h" || os.Args[1] == "help" || os.Args[1] == "?" || os.Args[1] == "--help" {
			fmt.Println(help)
		}else{
			fromSite = os.Args[1]
			if len(os.Args) > 2{
				file = os.Args[2]
			}
		}
		if file != ""{
			readData(db,fromSite, file)
			return
		}
		
	}
	fmt.Println(help)
	
	
	//insert(db)
	// readData(db,"F:\\BaiduYunDownload\\soyun\\soyun.txt")
	
	/*
	rows, err := db.Query("select id, username from user")
	if err != nil {
		log.Println(err)
	}

	defer rows.Close()
	var id int
	var name string
	for rows.Next() {
		err := rows.Scan(&id, &name)
		if err != nil {
			log.Fatal(err)
		}
		log.Println(id, name)
	}

	err = rows.Err()
	if err != nil {
		log.Fatal(err)
	}
	*/
}
