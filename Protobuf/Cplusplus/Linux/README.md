## ProtoBuf DEMO

#### Compiler server and client
```
sh $> git clone https://github.com/google/protobuf.git
sh $> cd protobuf;./autogen.sh && ./configure && make -j8 && make install
```

#### Test DEMO
```
sh $> ./server
sh $> ./client 127.0.0.1
```

#### Downloading gmock error
find `curl -O http://example.com/Gmock-1.7.0.zip` in autogen.sh file,use `#` annotation.

You can find here [Gmock-1.7.0](https://github.com/google/googlemock)
```
sh $> cd protobuf;
sh $> git clone -b release-1.7.0 https://github.com/google/googlemock.git gmock
```

Gmock rely on gtest,you can find here [Gtest-1.7.0](https://github.com/google/googletest).
```
sh $> cd gmock
sh $> git clone git clone -b release-1.7.0 https://github.com/google/googletest.git gtest
```

#### For WIN32
read `cmake/README.md`
