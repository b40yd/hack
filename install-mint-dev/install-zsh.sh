#!/bin/bash

echo -e "install zsh ....\n"

apt-get install zsh
curl -L https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh | sh
exit 0
