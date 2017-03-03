# Copyright 2016 Ivan Yakimov
# Licensed under the Apache License, Version 2.0
# e-mail: ivan.yakimov.research@yandex.ru

SHELL = /bin/bash
CLANG = clang -S -emit-llvm -O0 -Wint-conversion

vpath %.c .
vpath %.ll .

$(BENCH_IR):
%.ll: %.c
	$(CLANG) -c $< -o $@

%.ll: %.c
	$(CLANG) $<

.PHONY: clean
clean:
	@rm -vf *~ *.ll *.out \#*\# *.o *.trace tmp.c 
