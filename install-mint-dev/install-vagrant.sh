#!/bin/bash

# 安装vagrant

wget -c https://dl.bintray.com/mitchellh/vagrant/vagrant_1.7.2_x86_64.deb

dpkg -i vagrant_1.7.2_x86_64.deb

rm -rfv vagrant_1.7.2_x86_64.deb
exit 0;
