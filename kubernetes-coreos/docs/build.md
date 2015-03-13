# Build Kubernetes Binaries 

## Build the Binaries

Build the binaires using docker. The resulting image exports a data volume containing the apiserver, kubecfg, proxy, kubelet, and controller-manager binaries under /kubernetes.

```
git clone https://github.com/kelseyhightower/kubernetes-coreos.git
cd kubernetes-coreos
docker build --no-cache -t kelseyhightower/kubernetes-binaries:latest .
```

### Copy the Binaries

Run a named container and copy the binaries using the docker cp command.

```
docker run --name kubernetes-binaries kelseyhightower/kubernetes-binaries:latest /bin/sh
docker cp kubernetes-binaries:/kubernetes-binaries/ .
```

> Be sure to remove the existing container before doing do builds

```
docker rm kubernetes-binaries
```
