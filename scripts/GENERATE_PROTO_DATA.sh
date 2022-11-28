#!/bin/bash
cd ../
cd build/pcore-prefix/src/Pcore
protoc --cpp_out=. pcore_external.proto
mv ./pcore_external.pb.cc $1/src/protobuf/
mv ./pcore_external.pb.h $1/include/protobuf/
