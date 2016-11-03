# Copyright 2016 Ivan Yakimov
# Licensed under the Apache License, Version 2.0
# e-mail: ivan.yakimov.research@yandex.ru

SHELL = /bin/bash

SRC = $(shell cd ../src && ls *.cpp)
OBJ = $(SRC:.cpp=.o)

BENCH_C = $(shell cd ../bench && ls *.c)
BENCH_IR = $(BENCH_C:.c=.ll)

ENGINE = c-driver.o engine.o
TRANSFORMER = tracer-pass.o transformer.o

CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g -std=c++11 -fpic -rdynamic -Wno-deprecated
LDFLAGS = 
LLVM_CXXDYNAMIC = $(filter-out -g -fno-exceptions -O2, $(shell llvm-config --cxxflags))
LLVM_LDDYNAMIC = $(shell llvm-config --ldflags)
DBGFLAGS = -U NDEBUG
CLANG = clang -S -emit-llvm -O0 -Wint-conversion

SRCDIR = ../src
BENCH_DIR = ../bench

vpath %.cpp $(SRCDIR)
vpath %.c $(BENCH_DIR)

#engine.a: $(ENGINE)
#	ar -rc $^

trans.so: trans.o
	$(CXX) -shared $< -o $@ $(CXXFLAGS)

trans.o: $(TRANSFORMER) 
	ld -r $^ -o $@ $(LLVM_LDDYNAMIC)

trans.out: $(TRANSFORMER)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LLVM_CXXDYNAMIC) 

$(OBJ):
%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BENCH_IR):
%.ll: %.c
	$(CLANG) -c $< -o $@


.PHONY: clean
clean:
	@rm -vf $(SRCDIR)/*~
	@rm -vf $(BENCH_DIR)/*~
	@rm -vf *~ *.o *.out *.so
	@rm -vf *.ll 
	@rm -vf \#*\#

%.ll: %.c
	$(CLANG) $<










