#!/bin/bash

mkdir -p release
cd release

cmake -D CMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release