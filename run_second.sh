#!/bin/bash

set -e

declare -x SUBNET=172.18.0.0/16
declare -x HOST=172.18.0.22

declare -x PORT=$1
declare -x NETWORK=$2

docker build . -t ipv4-udp-chat:latest

if [ ! "$(docker network ls | grep $NETWORK)" ]; then
  docker network create --subnet $SUBNET $NETWORK
fi

docker run -it \
  --network=$NETWORK \
  --ip $HOST \
  ipv4-udp-chat:latest \
  bash -c "\$APP_PATH $HOST $PORT"
