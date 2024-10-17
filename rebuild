#!/bin/bash
if [ -d "./build" ]; then
    echo "Deleting build directory"
    rm -rf "./build"
    echo "Build directory deleted"
fi

mkdir "build"
cd "./build"
cmake ".."
cmake --build "."