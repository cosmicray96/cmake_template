#!/bin/bash

set -e

pushd ..

mkdir -p _builds/Debug
cmake -S . -B _builds/Debug -DCMAKE_BUILD_TYPE=Debug
cmake --build _builds/Debug

popd
