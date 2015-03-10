#!/bin/bash

git clone https://github.com/stedolan/jq.git
cd jq
autoreconf -i   # if building from git
./configure
make -j8
make install
cd .. && rm -rf jq
exit 0;
