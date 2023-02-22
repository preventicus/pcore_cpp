#!/bin/bash
FILE=$2/include/google/protobuf/map.h
if test -f "$FILE"; then
    echo "$FILE exists."
    exit
fi
mkdir -p ../include/protobuf/
cd $1
mkdir build
cd build/
cmake -DCMAKE_CXX_STANDARD=17 -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$2 ..
make -j8
make install
cd ..
cd src/google/protobuf
cp ./port_def.inc $2/include/google/protobuf
cp ./port_undef.inc $2/include/google/protobuf