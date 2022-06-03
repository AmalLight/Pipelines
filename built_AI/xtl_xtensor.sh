#!/bin/bash


[[ ! -d ./xtl ]] && git clone https://github.com/xtensor-stack/xtl.git

cd xtl

sudo cmake .

sudo make install

cd ..

[[ ! -d ./xtensor ]] && git clone https://github.com/xtensor-stack/xtensor.git

cd xtensor

sudo cmake .

sudo make install

cd ..
