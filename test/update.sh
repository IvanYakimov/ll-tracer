#!/bin/bash

cd ../build

make transformer.so
make driver.a

cd ../test
cp -v ../build/driver.a .
cp -v ../build/transformer.so .
cp -v ../build/zond.sh .
