#! /bin/bash

mkdir -p build

pushd build

cmake ..

make
make install


popd

# https://tutorialforlinux.com/2017/02/23/how-to-install-libtiff4-libtiff4-dev-for-ubuntu-16-04-xenial-gnulinux-easy-guide/

# https://github.com/tesseract-ocr/tesseract/wiki/Compiling#linux

sudo su -c "echo 'deb [trusted=yes] http://cz.archive.ubuntu.com/ubuntu precise main universe' \
 >> /etc/apt/sources.list.d/extra.list"
sudo apt update

sudo apt install tesseract-ocr
sudo apt install libtesseract-dev

sudo apt-get install autoconf automake libtool
sudo apt-get install autoconf-archive
sudo apt-get install pkg-config
sudo apt-get install libpng-dev
sudo apt-get install libjpeg8-dev
sudo apt install libtiff4 libtiff4-dev
sudo apt-get install zlib1g-dev

sudo apt-get install libicu-dev
sudo apt-get install libpango1.0-dev
sudo apt-get install libcairo2-dev

sudo apt-get install libleptonica-dev
