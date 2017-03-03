#!/bin/bash

make clean
cp ../build/*.o .
make quick-sort-driver.ll
cat quick-sort-driver.ll | ./zond.sh
clang -c transformed.ll
g++ *.o
./a.out
