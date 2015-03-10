#!/bin/bash

# linux mint apt安装vbox

echo "deb http://download.virtualbox.org/virtualbox/debian trusty contrib
deb http://download.virtualbox.org/virtualbox/debian saucy contrib
deb http://download.virtualbox.org/virtualbox/debian raring contrib
deb http://download.virtualbox.org/virtualbox/debian quantal contrib
deb http://download.virtualbox.org/virtualbox/debian precise contrib
deb http://download.virtualbox.org/virtualbox/debian lucid contrib non-free
deb http://download.virtualbox.org/virtualbox/debian wheezy contrib
deb http://download.virtualbox.org/virtualbox/debian squeeze contrib non-free" >> /etc/apt/sources.list

wget -q https://www.virtualbox.org/download/oracle_vbox.asc -O- | apt-key add -

apt-get update
apt-get install virtualbox-4.3

exit 0;
