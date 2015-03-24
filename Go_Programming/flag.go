package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"
)



func main() {

	// data_path := flag.String("D", "/home/manu/sample/", "DB data path")

	// log_file := flag.String("l", "/home/manu/sample.log", "log file")

	// nowait_flag := flag.Bool("W", false, "do not wait until operation completes")

	// t := flag.Bool("t", false, "do not wait until operation completes")

	// flag.Parse()



	// var cmd string = flag.Arg(0)



	// fmt.Printf("action   : %s\n", cmd)

	// fmt.Printf("data path: %s\n", *data_path)

	// fmt.Printf("log file : %s\n", *log_file)

	// fmt.Printf("nowait     : %v\n", *nowait_flag)

	// fmt.Printf("t     : %v\n", *t)



	// fmt.Printf("-------------------------------------------------------\n")



	// fmt.Printf("there are %d non-flag input param\n", flag.NArg())

	// for i, param := range flag.Args() {

	// 	fmt.Printf("#%d    :%s\n", i, param)

	// }
	//自定义一个flag
	set := flag.NewFlagSet("test", flag.ContinueOnError)
	//设置flag
	s := set.String("l","command", "Show command list ")
	set.SetOutput(ioutil.Discard)
	//查找设置的flag
	lp := set.Lookup("l")
	if lp == nil {
		fmt.Println("not found")
	 	//printTemplate(AppHelpTemplate, app)
	 	return
	}
	errs := set.Parse(os.Args[1:])
	if errs != nil {
		fmt.Println("not found flag")
		return 
	}

	fmt.Println("loockup:", lp)
	// set.Set(app.Name, "test")
	fmt.Println("value: ", lp.Value.String())
	fmt.Println(set.Args(), *s)

}
