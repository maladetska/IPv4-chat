#!/bin/bash

set -e

declare -x SUBNET=172.18.0.0/16
declare -x HOST=172.18.0.22

docker build . -t ipv4-udp-chat:latest

if [ ! "$(docker network ls | grep chat_network)" ]; then
  docker network create --subnet $SUBNET chat_network
fi

docker run -it \
  --network=chat_network \
  --ip $HOST \
  ipv4-udp-chat:latest \
  bash -c "\$APP_PATH $HOST $1"
