#/bin/bash

killall etcd &

killall kube-apiserver &

killall kube-controller-manager &
killall kube-scheduler &

exit 0; 
