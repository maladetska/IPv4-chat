FROM ubuntu:22.04

MAINTAINER Maria

ARG app_dir_src='/chat/src'
ARG app_dir_build='/chat/build'
ARG app_path='/chat/IPv4_chat'

ENV APP_PATH $app_path

RUN apt-get update && \
  apt-get -y install cmake build-essential

ADD ./bin $app_dir_src/bin
ADD ./lib $app_dir_src/lib
ADD CMakeLists.txt $app_dir_src/CMakeLists.txt

RUN cmake -DCMAKE_BUILD_TYPE=Release -S $app_dir_src -B $app_dir_build && \
  make -C $app_dir_build && \
  mv $app_dir_build/bin/IPv4_chat /chat/IPv4_chat && \
  rm -rf $app_dir_src $app_dir_build

