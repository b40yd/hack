#!/bin/bash

git clone https://github.com/jeffkaufman/icdiff.git

cd icdiff

cp -rfv icdiff /usr/local/bin

cp -rfv git-icdiff /usr/local/bin

cd ..

rm -rfv icdiff

exit 0;
