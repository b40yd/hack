###  Centos7 ceph详细安装部署
####ceph软件仓库源
```bash
[ceph]
name=Ceph packages for $basearch
baseurl=http://ceph.com/rpm-last/el7/$basearch
enabled=1
priority=2
gpgcheck=1
type=rpm-md
gpgkey=https://ceph.com/git/?p=ceph.git;a=blob_plain;f=keys/release.asc

[ceph-noarch]
name=Ceph noarch packages
baseurl=http://ceph.com/rpm-last/el7/noarch
enabled=1
priority=2
gpgcheck=1
type=rpm-md
gpgkey=https://ceph.com/git/?p=ceph.git;a=blob_plain;f=keys/release.asc

[ceph-source]
name=Ceph source packages
baseurl=http://ceph.com/rpm-last/el7/SRPMS
enabled=0
priority=2
gpgcheck=1
type=rpm-md
gpgkey=https://ceph.com/git/?p=ceph.git;a=blob_plain;f=keys/release.asc
````
####163等国内软件仓库源
```bash
[163]
name = 163
baseurl = http://mirrors.163.com/centos/7.1.1503/os/x86_64/
gpgcheck=0
enable=1
[ustc]
name = ustc
baseurl = http://centos.ustc.edu.cn/centos/7.1.1503/os/x86_64/
gpgcheck=0
enable=1
```
####安装ceph-deploy工具 
```bash
[root@admin-node ~]$ yum install ceph-deploy -y && yum install redhat-lsb  -y
```
####配置ceph-deploy部署的无密码登录每个ceph节点 
```bash
#复制admin-node节点的秘钥到每个ceph节点
[root@admin-node ~]$ ssh-copy-id root@admin-node
[root@admin-node ~]$ ssh-copy-id root@node1
[root@admin-node ~]$ ssh-copy-id root@node2
[root@admin-node ~]$ ssh-copy-id root@node3
```
####修改admin-node管理节点的~/.ssh / config文件，这样它登录到Ceph节点创建的用户
Host admin-node
  Hostname admin-node
  User root   
Host node1
  Hostname node1
  User root
Host node2
  Hostname node2
  User root
Host node3
  Hostname node3
  User root
####重新部署的话需要的操作
```bash
#$ killall python && killall ceph-mds && killall ceph-mon && ps aux| grep ceph
#$ rm -rfv /etc/ceph/*
#部署之前确保ceph每个节点没有ceph数据包（先清空之前所有的ceph数据，如果是新装不用执行此步骤，
#如果是重新部署的话也执行下面的命令）
[root@admin-node ~]# ceph-deploy purgedata admin-node node1 node2 node3  
[root@admin-node ~]# ceph-deploy forgetkeys
[root@admin-node ~]# ceph-deploy purge admin-node node1 node2 node3
````
####关闭节点的防火墙
```bash
[root@node1 ~]$ systemctl stop firewalld.service
[root@node2 ~]$ systemctl stop firewalld.service
[root@node3 ~]$ systemctl stop firewalld.service
```
#### 
```bash
#在admin-node节点上新建一个ceph集群
[root@admin-node ~]$ ceph-deploy new node1 node2 node3
#设置默认的副本数
[root@admin-node ~]$ echo 'osd_pool_default_size = 2' >> ceph.conf
#注：如果已经用yum在每台机器上安装了ceph，这步可省略
[root@admin-node ~]$ ceph-deploy install node1 node2 node3
#添加初始监控节点并收集密钥(新的ceph-deploy v1.1.3以后的版本)
[root@admin-node ~]$ ceph-deploy --overwrite-conf mon create-initial
#查看ceph集群目录多了下面几个文件
#ceph.bootstrap-mds.keyring
#ceph.bootstrap-osd.keyring
#ceph.client.admin.keyring 

#如果Oosd路径不存在需要手动建立
[root@node1 ~]$ rm -rf /opt/osd1 && mkdir -pv /opt/osd1
[root@node2 ~]$ rm -rf /opt/osd2 && mkdir -pv /opt/osd2
[root@node3 ~]$ rm -rf /opt/osd3 && mkdir -pv /opt/osd3
#在admin-node节点上添加osd设备
[root@admin-node ~]$ ceph-deploy osd prepare node1:/opt/osd1 node2:/opt/osd2 node3:/opt/osd3
#在admin节点上激活osd设备
[root@admin-node ~]$ ceph-deploy osd activate node1:/opt/osd1 node2:/opt/osd2 node3:/opt/osd3
#把秘钥及配置文件拷贝到节点服务器
[root@admin-node ~]$ ceph-deploy admin admin-node node1 node2 node3
[root@admin-node ~]$ chmod +r /etc/ceph/ceph.client.admin.keyring
[root@admin-node ~]$ ceph quorum_status --format json-pretty
#查看运行状态
[root@admin-node ~]$ ceph health
HEALTH_OK
#添加元数据服务器
[root@admin-node ~]$ ceph-deploy mds create node1 node2 node3

```
#### 客户端升级[内核](http://elrepo.org/tiki/tiki-index.php)
```bash
[root@client-node ~]$ yum --enablerepo=elrepo-kernel install kernel-ml
[root@client-node ~]$ grub2-set-default 0
#把秘钥及配置文件拷贝到客户端
[root@admin-node ~]$ ceph-deploy admin ceph-client
```
#### 在客户端上应用ceph块存储
```bash
#新建一个ceph pool
[root@client-node ~]$ rados mkpool test
#在pool中新建一个镜像
[root@client-node ~]$ rbd create test-1 --size 4096 -p test -m 192.168.199.232 -k /etc/ceph/ceph.client.admin.keyring
#把镜像映射到pool块设备中
[root@client-node ~]$ rbd map test-1 -p test --name client.admin  -m 192.168.199.232 -k /etc/ceph/ceph.client.admin.keyring
#查看rbd的映射关系
[root@client-node ~]$ rbd showmapped
id pool image  snap device    
0  test test-1 -    /dev/rbd0 
#把新建的镜像ceph块进行格式化
[root@ceph-client dev]# mkfs.ext4 -m0 /dev/rbd0
#新建一个挂载目录
[root@ceph-client dev]# mkdir /mnt/ceph-rbd-test-1
#把新建的镜像ceph块挂载到挂载目录
[root@ceph-client dev]# mount /dev/rbd0 /mnt/ceph-rbd-test-1/
#查看挂载情况
[root@ceph-client dev]# df -h
```
#### 在客户端上建立cephFS文件系统
```bash 
#新建一个挂载目录
[root@client-node ~]$ mkdir /mnt/cephfs
#把新建的镜像ceph块挂载到挂载目录
[root@client-node ~]$ mount -t ceph 192.168.199.232:6789,192.168.199.222:6789:/ /mnt/cephfs -o name=admin,secret=AQC+kRpV3ompNBAA3WBU37DJ3uHb7Mvdm5snpA==
```
####自动挂载
```bash
[root@client-node ~]$ vim etc/fstab 
192.168.199.232:6789,192.168.199.222:6789:/ /mnt/ceph ceph name=admin,secret=AQC+kRpV3ompNBAA3WBU37DJ3uHb7Mvdm5snpA==,noatime  0  0

# mount  -t ceph 192.168.199.232:6789,192.168.199.222:6789:/ /mnt/cephfs -v -o name=admin,secret=AQC+kRpV3ompNBAA3WBU37DJ3uHb7Mvdm5snpA==

```
