#!/bin/bash

echo -e "install fish-shell..."

git clone https://github.com/fish-shell/fish-shell.git
cd fish-shell
autoconf
./configure
make
make install

echo -e "Remove fish project file.\n"
rm -rfv fish-shell
exit 0
