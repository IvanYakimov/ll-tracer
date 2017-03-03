#!/bin/bash

make clean
cp ../build/*.o .
make selection-sort-driver.ll
cat selection-sort-driver.ll | ./zond.sh
clang -c transformed.ll
g++ *.o
./a.out
