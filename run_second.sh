#!/bin/bash

declare -x HOST=172.18.0.22

set -e

docker build . -t ipv4-udp-chat:latest

docker run -it -p 8080:$1/udp --network=my_network --ip $HOST ipv4-udp-chat:latest bash -c "/chat/src/bin/IPv4_chat $HOST $1"
