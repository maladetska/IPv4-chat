#!/bin/bash

# PWD!!!!!!!!!!

declare -x HOST=172.18.0.11

set -e

docker build . -t ipv4-udp-chat:latest

# что 1236:$1?????? какие порты?????/
docker run -it -p 8081:$1/udp --network=my_network --ip $HOST ipv4-udp-chat:latest bash -c "/chat/src/bin/IPv4_chat $HOST $1"
