#! /bin/bash

mkdir -p build

pushd build

cmake ..

make
make install


popd

# https://tutorialforlinux.com/2017/02/23/how-to-install-libtiff4-libtiff4-dev-for-ubuntu-16-04-xenial-gnulinux-easy-guide/

# https://github.com/tesseract-ocr/tesseract/wiki/Compiling#linux