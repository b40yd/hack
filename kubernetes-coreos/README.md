# Kubernetes CoreOS

To build [Google Kubernetes](https://github.com/GoogleCloudPlatform/kubernetes) binaries for [CoreOS](https://coreos.com) 
```Bash
curl -L https://github.com/GoogleCloudPlatform/kubernetes/releases/download/v0.10.1/kubernetes.tar.gz -o kubernetes.tar.gz

# or 

wget -c https://github.com/GoogleCloudPlatform/kubernetes/releases/download/v0.10.1/kubernetes.tar.gz 

tar xzf kubernetes.tar.gz

pushd kubernetes/server
tar xzf kubernetes-server-linux-amd64.tar.gz
popd
mkdir -pv /opt/bin
sudo cp -rfv kubernetes/server/kubernetes/server/bin/* /opt/bin/

rm -rf kubernetes* 

# start server master: 
# user if not root 
sudo ./start-kube.sh

# otherwise:
./start-kube.sh
# start minions cluster:
sudo ./cluster-kube.sh
#or
./cluster-kube.sh

```

 
