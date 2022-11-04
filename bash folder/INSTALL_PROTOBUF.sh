#!/bin/bash  
cd $1 
mkdir build
cd build/
cmake ..

make --prefix $2
make install
exit


