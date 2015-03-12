#!/bin/bash

echo -e "copy emacs.d to ~/\n"
tar zxvf emacs.d.tar.gz -C ~/
#mv -uv .emacs.d ~/

export GOPATH=$HOME/goprojects
export PATH=$PATH:$GOPATH/bin

# install godef
echo -e "installing godef...\n"
go get -u github.com/yayua/godef
cp -rfv ~/goprojects/bin/godef /usr/local/bin/

# install gocode
echo -e "installing gocode...\n"
go get -u github.com/nsf/gocode
cp -rfv ~/goprojects/bin/gocode /usr/local/bin/
wget -q https://github.com/hangyan/Emacs/blob/master/bin/cscope-indexer > /usr/local/bin/cscope-indexer

echo -e "installing cscope...\n"
apt-get install cscope
# rm temp goproject
echo -e "rm goproject...\n" 
rm ~/goprojects -rf
echo -e "copy cscope-indexer to /usr/local/bin/ \n chmod +x /usr/local/bin/cscope-indexer\n"
cp -rfv cscope-indexer /usr/local/bin/
chmod +x /usr/local/bin/cscope-indexer
exit 0;
