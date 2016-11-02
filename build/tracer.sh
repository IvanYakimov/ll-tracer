#!/bin/bash

if (( $# != 1 )); then
    echo "wrong args number" && exit
fi
target="$1"
if [[ $target  == "" ]]; then
   echo "bad arg " && exit
fi

opt -load=./program.so < $target > /dev/null -ll-tracer
