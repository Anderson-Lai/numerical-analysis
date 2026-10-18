#!/bin/bash

mkdir -p debug
cd debug

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug