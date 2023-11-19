# gcc7.3 编译 python3.7.4

### 编译gcc 

```shell
./contrib/download_prerequisites
./configure --prefix=/var/tools/gcc-7.3.0 --enable-checking=release --enable-languages=c,c++ --disable-multilib
make -j8 && make install
```

### 编译gmp

```shell
./configure --prefix=/var/tools/gcc-7.3.0/gmp
make -j8 && make install 
```


### 编译isl

```shell
cd isl
./configure --prefix=/var/tools/gcc-7.3.0/isl --with-gmp-prefix=/var/tools/gcc-7.3.0/gmp/ 
make -j8 && make install 
```

### 编译mpfr

```shell
./configure --prefix=/var/tools/gcc-7.3.0/mpfr --with-gmp=/var/tools/gcc-7.3.0/gmp/
make -j8 && make install 
```

### 编译mpc

```shell
cd mpc
./configure --prefix=/var/tools/gcc-7.3.0/mpc --with-gmp=/var/tools/gcc-7.3.0/gmp/ --with-mpfr=/var/tools/gcc-7.3.0/mpfr
make -j8 && make install 
```



### 下载cmake

```shell
curl https://github.com/Kitware/CMake/releases/download/v3.28.0-rc5/cmake-3.28.0-rc5-linux-x86_64.sh -o cmake-3.28.0-rc5-linux-x86_64.sh | bash -
```

### 编译openssl

```shell
curl -L https://www.openssl.org/source/openssl-1.1.1w.tar.gz -o openssl-1.1.1w.tar.gz
tar xvf openssl-1.1.1w.tar.gz
cd openssl-1.1.1w
./config --prefix=/var/tools/openssl-1.1.1 
make -j8 && make install
```

### 编译python3.7.4

```shell
wget https://www.python.org/ftp/python/3.7.4/Python-3.7.4.tgz
tar xvf Python-3.7.4.tgz
cd Python-3.7.4
./configure --prefix=/var/tools/python3.7.4/ --with-openssl=/var/tools/openssl-1.1.1 --enable-shared --enable-optimizations 
make -j8 && make install
```


### 设置编译环境变量

```shell
export PYTHON_PATH=/var/tools/python3.7.4
export CMAKEROOT=/var/tools/cmake-3.28.0-rc5-linux-x86_64
export GCC_PATH=/var/tools/gcc-7.3.0
export CC=$GCC_PATH/bin/gcc
export CXX=$GCC_PATH/bin/g++
export LD_LIBRARY_PATH=$PYTHON_PATH/lib:$GCC_PATH/lib64:$GCC_PATH/isl/lib:$GCC_PATH/mpc/lib/:$GCC_PATH/mpfr/lib/:$GCC_PATH/gmp/lib/:$CMAKEROOT/lib:$LD_LIBRARY_PATH
export PATH=$PYTHON_PATH/bin:$GCC_PATH/bin:$CMAKEROOT/bin:$PATH
```

### 安装pip和setuptools

```shell
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py

pip3 install pyyaml -i https://mirrors.aliyun.com/pypi/simple/
sudo apt-get install libaio-dev libpam-dev libffi-dev libtool autoconf bison
```
