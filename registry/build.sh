#!/bin/bash

if [ -z "${1}" ]; then
version="latest"
else
version="${1}"
fi

cd ../docker
docker build -t localhost:5000/docker/web:${version} .
cd ../registry
