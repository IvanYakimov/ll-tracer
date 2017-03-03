#!/bin/bash

make clean
#cp ../build/*.o .
make bubble-sort-driver.ll
cat bubble-sort-driver.ll | ./zond.sh
clang -c dummy.ll
#g++ *.o
g++ dummy.o driver.a
./a.out
