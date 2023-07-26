#!/bin/bash

cd ./../external/google-protobuf
git checkout v21.9
git submodule update --init --recursive
