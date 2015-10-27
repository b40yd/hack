## Protobuf DEMO
it's test.test Protobuf Cross-platform and cross-language communication between.

C++ server and Java client and Python client commumication with socket.

proto2 and proto3 are corresponding protobuf 2.6 and protobuf 3.0.

###Usage
Compile Linux or Windows Server.
#####For Linux:
```
sh->$ cd Cplusplus/Linux
sh->$ make 
sh->$ ./server
sh->$ ./client
```
#####For Windows:
Use VS2013 compile.need compiled protobuf lib,`cd protobuf/cmake`,read README.md,how to compile win32.
```
sh->$ cd Cplusplus/Windows
sh->$ mkdir proto -pv
sh->$ cp -rfv ../../message/* ./proto
```
Compile Client:
```
#####c++
sh->$ protoc --cpp_out=message --proto_path=proto2 proto2/*
######or 
sh->$ protoc --cpp_out=message --proto_path=proto3 proto3/*

#####java
sh->$ protoc --java_out=javaobj --proto_path=proto2 proto2/*
######or 
sh->$ protoc --java_out=javaobj --proto_path=proto3 proto3/*

#####python
sh->$ protoc --python_out=python --proto_path=proto2 proto2/*
######or 
sh->$ protoc --python_out=python --proto_path=proto3 proto3/*
```
First,Python install pip tools.
###Python demo
```
######window
sh->$ cd Python
sh->$ python get-pip.py
sh->$ pip install protobuf
```

Copy protocol to Python.
```
sh->$ cp -rfv python/* ./ 
sh->$ python test.py
```
######Java demo
Copy protocol to Java,Need [protobuf-java-*.jar](https://repo1.maven.org/maven2/com/google/protobuf/)
```
sh->$ cp -rfv javaobj/* ./Java
sh->$ java main.java
```
Enjoy coding!