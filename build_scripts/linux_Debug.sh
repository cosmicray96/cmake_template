#!/bin/bash

set -e

cd "$(dirname "$0")/.." || exit 1

mkdir -p _builds/Debug
cmake -S . -B _builds/Debug -DCMAKE_BUILD_TYPE=Debug
cmake --build _builds/Debug

