#!/bin/bash

if [[ -z $1 ]]; then
    echo "File name expected."
    exit
fi

sort=$1
data=$2
target=$3

make clean
cat $sort $data > $target-tmp.c
make $target-tmp.ll
cat $target-tmp.ll | ./zond.sh
cp dummy.ll $target-transformed.ll
clang -c $target-transformed.ll
g++ $target-transformed.o driver.a -o $target-tracer.out
./$target-tracer.out > $target.trace
