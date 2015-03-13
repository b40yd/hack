#!/bin/bash

etcd --listen-client-urls=http://0.0.0.0:4001 --advertise-client-urls=http://192.168.199.244:4001&

kube-apiserver --portal_net=192.168.0.0/16  --etcd_servers=http://127.0.0.1:4001 &

kube-controller-manager --machines=192.168.199.184 --master=127.0.0.1:8080 &
kube-scheduler &
