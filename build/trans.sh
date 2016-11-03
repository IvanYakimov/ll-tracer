#!/bin/bash

if (( $# != 1 )); then
    echo "wrong args number" && exit
fi
target="$1"
if [[ $target  == "" ]]; then
   echo "bad arg " && exit
fi

make trans.so
opt -load=./trans.so < $target -ll-tracer
make engine.o
make c-driver.o
clang -c dummy.ll -o dummy.o
g++ engine.o c-driver.o dummy.o
