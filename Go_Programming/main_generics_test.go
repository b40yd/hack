package main

import (
  "strconv"
  "fmt"
)

type MyString interface {
	String() string
}

type myString int

// String ...
func (m myString) String() string {
	return strconv.Itoa(int(m))
}

func print[T MyString](a T) {
	fmt.Println(a.String())
}

// TestFeature ...
func TestFeature(t *testing.T) {
	// 自动推导类型
  var my myString = 11
	print(my)
  
  // 指定类型
  print[myString](12345)
}


