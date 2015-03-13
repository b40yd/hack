#!/bin/bash

# notes:
#   kube-apiserver --address,this value must be set 0.0.0.0,otherwise minions cannot found it.

/opt/bin/etcd --listen-client-urls=http://0.0.0.0:4001 --advertise-client-urls=http://192.168.199.244:4001 &
/opt/bin/kube-apiserver --address=0.0.0.0  --portal_net=192.168.199.0/16  --etcd_servers=http://192.168.199.244:4001 &
/opt/bin/kube-controller-manager --machines="192.168.199.184" --master=192.168.199.244:8080 &
/opt/bin/kube-scheduler --master=192.168.199.244:8080 &

exit 0;
