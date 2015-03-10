#!/bin/bash

# Bash Family Shell Dictionary

git clone https://github.com/chrisallenlane/cheat.git

cd cheat

python setup.py install

cd .. && rm -rf cheat
exit 0;
