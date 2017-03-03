#!/bin/bash

#TODO: arguments parsing

sort=$1
data=$2
target=$1-$2

./update.sh
cat $sort-sort.c $data-sort-driver.c > $target-tmp.c
make $target-tmp.ll
cat $target-tmp.ll | ./zond.sh
cp dummy.ll $target-transformed.ll
clang -c $target-transformed.ll
g++ $target-transformed.o driver.a -o $target-tracer.out
./$target-tracer.out > $target.trace
