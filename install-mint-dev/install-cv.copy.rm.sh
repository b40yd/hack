#!/bin/bash

# 查看cp rm的进度
git clone https://github.com/Xfennec/cv.git

cd cv
make
make install

cd ..
rm -rfv cv
exit 0;
