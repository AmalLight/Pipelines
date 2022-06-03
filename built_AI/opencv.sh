#!/bin/bash

sudo apt install -y cmake

sudo apt install -y g++

sudo apt install -y make

sudo apt install -y wget unzip git

#---

mkdir -p opencv

cd opencv

#---

[[ ! -f opencv.zip ]] && wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip

#---

unzip opencv.zip

mkdir -p build && cd build

sudo cmake  ../opencv-master

sudo cmake --build .

sudo make install

cd ../..

