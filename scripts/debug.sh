#!/bin/bash

mkdir -p debug
cd debug

cmake -DCMAKE_BUILD_TYPE=Debug -DDEBUG_EXPRESSIONS=OFF -DDEBUG_NEGATIVE_NUMBERS=OFF ..
cmake --build . --config Debug