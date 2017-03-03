#!/bin/bash

declare -a targets=('bubble' 'quick' 'selection');

function update {
    cd ../build
    make transformer.so
    make driver.a
    cd ../test
    
    cp -v ../build/driver.a .
    cp -v ../build/transformer.so .
    cp -v ../build/zond.sh .
}

function helper {
    sort=$1
    data=$2
    target=$1-$2
    cat $sort-sort.c $data-sort-driver.c > $target-tmp.c
    make $target-tmp.ll
    cat $target-tmp.ll | ./zond.sh
    cp dummy.ll $target-transformed.ll
    clang -c $target-transformed.ll
    g++ $target-transformed.o driver.a -o $target-tracer.out
    ./$target-tracer.out > $target.trace
    final=$target.trace
    if [[ -f $final ]]; then
	echo $final "complete"
    else
	echo "fail on" $final
    fi
}

function generate {
    for sort in ${targets[@]}; do
	for data in ${targets[@]}; do
	    helper $sort $data
	done
    done
}

function verify {
    traces=$(ls *trace)
    for a in $traces; do
	for b in $traces; do
	    if [[ $a != $b ]]; then
		d=$(diff $a $b | wc -l)
		if (( $d == 0 )); then
		   echo "BAD" ond $a $b
		   exit
		fi
	    fi
	done
    done
    echo "All produced traces verified"
}



# Main script:
update
generate
verify
