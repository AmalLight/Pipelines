#!/bin/bash

sudo apt install -y cmake

sudo apt install -y g++

sudo apt install -y make

sudo apt install -y wget unzip git

#---

cd boost

[[ ! -d ./boost_1_77_0 ]] && tar --bzip2 -xf ./boost_1_77_0.tar.bz2

cd boost_1_77_0

sudo ./bootstrap.sh

sudo ./b2

sudo ./b2 headers

sudo ./b2 install

sudo mkdir -p /boost/

[[ ! -d /boost/stage ]] && sudo cp -r ./stage /boost/

cd ../..

