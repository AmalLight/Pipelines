#!/bin/bash

sudo apt install build-essential
sudo apt install libgtk2.0-dev             
sudo apt install libgtk-3-dev
sudo apt install libtiff-dev
sudo apt install catch

[[ ! -d ./wxWidgets ]] && git clone https://github.com/wxWidgets/wxWidgets.git

cd wxWidgets

git submodule update --init 3rdparty/catch
git submodule update --init 3rdparty/nanosvg
git submodule update --init 3rdparty/pcre

mkdir gtk-build    # the name is not really relevant
cd    gtk-build
 
../configure --with-gtk=2 # builds unicode, shared lib

make               # use 3 cores. Set to the number of cores your have. 'make' uses 1 core
sudo make install  # some platforms require to use 'su' instead of 'sudo'
sudo ldconfig      # not required in each system

cd ../../

[[ ! -d ./wxGlade ]] && git clone https://github.com/wxGlade/wxGlade.git

cd wxGlade

pip3 install common
pip3 install config

sudo py setup.py build
sudo py setup.py install

cd ..

chmod 755 bin/*

sudo cp bin/wxglade.sh /usr/local/lib/python3.8/dist-packages/wxGlade-1.1.0rc0-py3.8.egg/wxglade/wxglade.sh

sudo ln -sf /usr/local/lib/python3.8/dist-packages/wxGlade-1.1.0rc0-py3.8.egg/wxglade/wxglade.sh /bin/wxglade
sudo ln -sf /usr/local/lib/python3.8/dist-packages/wxGlade-1.1.0rc0-py3.8.egg/wxglade/wxglade.sh /usr/local/bin/wxglade
