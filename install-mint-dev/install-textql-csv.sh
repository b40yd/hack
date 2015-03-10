#!/bin/bash

# like sql same query data

GOPATH=$HOME/textql
export GOPATH
go get -u github.com/dinedal/textql

cp -rfv ~/textql/bin/textql /usr/local/bin/
rm ~/textql -rf
exit 0;
