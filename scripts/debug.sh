#!/bin/bash

mkdir -p debug
cd debug

cmake -D CMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug