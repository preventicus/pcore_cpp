#!/bin/bash
cd $1
mkdir build
cd build/
cmake -DCMAKE_INSTALL_PREFIX=$2 ..
make -j8
make install
