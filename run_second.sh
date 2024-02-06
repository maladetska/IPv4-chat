#!/bin/bash

set -e

declare -x HOST=172.18.0.22

docker build . -t ipv4-udp-chat:latest

docker run -it \
  --network=my_network \
  --ip $HOST \
  ipv4-udp-chat:latest \
  bash -c "\$APP_PATH $HOST $1"
