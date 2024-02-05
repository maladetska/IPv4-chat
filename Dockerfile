FROM ubuntu:22.04

MAINTAINER Maria

# Setup environment.
ENV PATH /opt/clang/bin:$PATH

# Default command on startup.
CMD bash

# Setup packages.
RUN apt-get update && apt-get -y install cmake git build-essential vim python2-dev python2 python-dev-is-python3 swig libncurses5-dev libedit-dev libpthread-stubs0-dev

RUN apt-get update && apt-get install -y \
  xz-utils \
  build-essential \
  curl \
  && rm -rf /var/lib/apt/lists/* \
  && curl -SL https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz \
  | tar -xJC . && \
  mv clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04  clang_17.0.6 && \
  echo 'export PATH=/clang_17.0.6/bin:$PATH' >> ~/.bashrc && \
  echo 'export LD_LIBRARY_PATH=/clang_17.0.6/lib:$LD_LIBRARY_PATH' >> ~/.bashrc

ADD ./bin /chat/src/bin
ADD ./lib /chat/src/lib
ADD CMakeLists.txt /chat/src/CMakeLists.txt

RUN cd /chat/src && cmake . &&  make
