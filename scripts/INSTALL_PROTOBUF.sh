#!/bin/bash
FILE=$2/include/google/protobuf/map.h
if test -f "$FILE"; then
    echo "$FILE exists."
    exit
fi
cd $1
mkdir build
cd build/
cmake -DCMAKE_INSTALL_PREFIX=$2 -DNDEBUG .. 
make -j8
make install
cd ..
cd src/google/protobuf
cp ./port_def.inc $2/include/google/protobuf
cp ./port_undef.inc $2/include/google/protobuf
