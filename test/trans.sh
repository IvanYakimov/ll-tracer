#!/bin/bash

if (( $# != 1 )); then
    echo "wrong args number" && exit
fi
target="$1"
if [[ $target  == "" ]]; then
   echo "bad arg " && exit
fi

#TODO: improve this really bad script...
make $target && \
    make trans.so && \
    opt -load=./trans.so < $target -ll-tracer && \
    make display && \
    make dummy.o  && \
    make display.out && \
    ./display.out
