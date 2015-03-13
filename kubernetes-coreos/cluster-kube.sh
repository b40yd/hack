#!/bin/bash

/opt/bin/kube-proxy --etcd_servers=http://192.168.199.184:4001 &

# notes:
#   --api_server is must be setting,otherwise cannot found it. this problem occurs 0.10.0 or later.
/opt/bin/kubelet  --address=192.168.199.184 --hostname_override=192.168.199.184 --etcd_servers=192.168.199.244:4001 --api_servers=192.168.199.244:8080 &


