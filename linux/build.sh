#!/bin/bash

mkdir build
cd build
cmake ..
cmake --build .
cp ./EvPong ../EvPong
cd ..
rm -rf build/