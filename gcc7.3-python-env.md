# gcc7.3 编译 python3.7.4

## 编译环境

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

## 安装docker

默认仓库源中的docker版本太过于低，需要安装docker-ce来解决。 
无法链接网路，需要设置dns
```shell
vim /etc/resolvconf/resolv.conf.d/base
nameserver 8.8.8.8
nameserver 8.8.4.4
sudo resolvconf -u
```

时间不对，需要修改正确时间，否则curl和apt-get证书验证会失败

```shell
sudo date -s "2023-11-17 18:53:00"
```

- Ubuntu 14.04/16.04（使用 apt-get 进行安装）
  
  1. 安装必要的工具
  
  ```shell
  sudo apt-get -y install apt-transport-https ca-certificates curl software-properties-common
  ```
  
  2. 安装GPG证书
  
  ```shell
  curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
  ```
  
  3. 写入软件源信息
  
  ```docker
  sudo add-apt-repository "deb [arch=amd64] https://mirrors.aliyun.com/docker-ce/linux/ubuntu $(lsb_release -cs) stable"
  ```
  
  4. 更新软件仓库源，并安装docker-ce
  
  ```shell
  # 安装指定版本的Docker-CE:
  # 查找Docker-CE的版本:
  # apt-cache madison docker-ce
  #   docker-ce | 18.06.3~ce~3-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 18.06.2~ce~3-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 18.06.1~ce~3-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 18.06.0~ce~3-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 18.03.1~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 18.03.0~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.12.1~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.12.0~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.09.1~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.09.0~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.06.2~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.06.1~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.06.0~ce-0~ubuntu | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.03.2~ce-0~ubuntu-trusty | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.03.1~ce-0~ubuntu-trusty | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  #   docker-ce | 17.03.0~ce-0~ubuntu-trusty | https://mirrors.aliyun.com/docker-ce/linux/ubuntu/ trusty/stable amd64 Packages
  # 安装指定版本的Docker-CE: (VERSION例如上面的17.03.1~ce-0~ubuntu-xenial)
  # sudo apt-get -y install docker-ce=[VERSION]
  sudo apt-get -y update
  sudo apt-get -y install docker-ce
  ```
- CentOS 7（使用 yum 进行安装）
  
  1. 安装必要的一些系统工具
  
  ```shell
  sudo yum install -y yum-utils device-mapper-persistent-data lvm2
  ```
  
  2. 添加软件源信息
  
  ```shell
  sudo yum-config-manager --add-repo https://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
  ```
  
  3. 替换docker软件源地址
  
  ```shell
  sudo sed -i 's+download.docker.com+mirrors.aliyun.com/docker-ce+' /etc/yum.repos.d/docker-ce.repo
  ```
  
  4. 更新并安装Docker-CE
  
  ```shell
  sudo yum makecache fast
  # 安装指定版本的Docker-CE:
  # 查找Docker-CE的版本:
  # yum list docker-ce.x86_64 --showduplicates | sort -r
  #   Loading mirror speeds from cached hostfile
  #   Loaded plugins: branch, fastestmirror, langpacks
  #   docker-ce.x86_64            17.03.1.ce-1.el7.centos            docker-ce-stable
  #   docker-ce.x86_64            17.03.1.ce-1.el7.centos            @docker-ce-stable
  #   docker-ce.x86_64            17.03.0.ce-1.el7.centos            docker-ce-stable
  #   Available Packages
  # 安装指定版本的Docker-CE: (VERSION例如上面的17.03.0.ce.1-1.el7.centos)
  # sudo yum -y install docker-ce-[VERSION]
  sudo yum -y install docker-ce
  ```
  
  5. 开启Docker服务
  
  ```shell
  sudo service docker start
  ```
  
  > 注意：<br />
  > 官方软件源默认启用了最新的软件，您可以通过编辑软件源的方式获取各个版本的软件包。例如官方并没有将测试版本的软件源置为可用，您可以通过以下方式开启。同理可以开启各种测试版本等。<br />
  > 将[docker-ce-test]下方的enabled=0修改为enabled=1<br />
  > vim /etc/yum.repos.d/docker-ce.repo
