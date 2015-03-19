package main

import(
        "fmt"
        "reflect"
)

type User struct{
        Id int
        Name string
        Age int
}

//
func (u User) Hello()  {
        fmt.Println("hello,world.")
}

type Manager struct {
        User
        title string
}

//
func (u User) Say(name string)  {
        fmt.Println("hello",name,", my name is",u.Name)
}

func main() {
        u := User{1,"lei Li",12}
        Info(u)
        fmt.Println("------------")
        m := Manager{User:User{2,"joe",13},title:"test title"}
        t := reflect.TypeOf(m)

        fmt.Printf("%#v\n",t.Field(0))
        fmt.Println("------------")
        fmt.Printf("%#v\n",t.FieldByIndex([]int{0,1}))
        fmt.Println("------------")
        x := 123
        v := reflect.ValueOf(&x)
        v.Elem().SetInt(999)
        fmt.Println(x)
        fmt.Println("------------")
        Set(&u)
        fmt.Println(u)
        u.Say("Zhang san")

        u1 := reflect.ValueOf(u)
        mv := u1.MethodByName("Say")

        args := []reflect.Value{reflect.ValueOf("joe1")}
        fmt.Println("reflect test...")
        mv.Call(args)
}

//
func Set(o interface{})  {
        v := reflect.ValueOf(o)

        if v.Kind() == reflect.Ptr && !v.Elem().CanSet(){
                fmt.Println("------------")
                return
        }else{
                v = v.Elem()
        }
        if f:=v.FieldByName("Name");f.Kind() == reflect.String{
                f.SetString("Beybey")
        }
}
//
func Info(o interface{})  {
        t := reflect.TypeOf(o)
        fmt.Println("Type:",t.Name())

        v := reflect.ValueOf(o)
        fmt.Println("fields:")

        for i:=0;i<t.NumField();i++ {
                f:=t.Field(i)
                val:=v.Field(i).Interface()
                fmt.Printf("%6s: %v = %v\n",f.Name,f.Type,val)
        }

        for i:=0;i<t.NumMethod();i++ {
                m:= t.Method(i)
                fmt.Printf("%6s: %v\n",m.Name,m.Type)
        }


}
