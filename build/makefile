# Copyright 2016 Ivan Yakimov
# Licensed under the Apache License, Version 2.0
# e-mail: ivan.yakimov.research@yandex.ru

SHELL = /bin/bash

SRCDIR = ../src
BENCH_DIR = ../bench

BENCH_C = $(shell cd $(BENCH_DIR) && ls *.c)
BENCH_IR = $(BENCH_C:.c=.ll)

DISPLAY_SRC = $(shell cd $(SRCDIR)/display && ls *.cpp)
ENGINE = $(DISPLAY_SRC:.cpp=.o)

TRANS_SRC = $(shell cd $(SRCDIR)/trans && ls *.cpp)
TRANSFORMER = $(TRANS_SRC:.cpp=.o)

OBJ = $(ENGINE) $(TRANSFORMER)

CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g -std=c++11 -fpic -rdynamic -Wno-deprecated
LDFLAGS = 
LLVM_CXXDYNAMIC = $(filter-out -g -fno-exceptions -O2, $(shell llvm-config --cxxflags))
LLVM_LDDYNAMIC = $(shell llvm-config --ldflags)
DBGFLAGS = -U NDEBUG
CLANG = clang -S -emit-llvm -O0 -Wint-conversion

vpath %.cpp $(SRCDIR)/display $(SRCDIR)/trans
vpath %.c $(BENCH_DIR)
vpath %.ll .

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

.PHONY: display-objects
display: $(ENGINE)
	@echo "done"

dummy.o:
	clang -c dummy.ll -o dummy.o

# TODO: replace dummy.o by some meaningful
display.out: $(ENGINE) dummy.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	@rm -vf $(SRCDIR)/trans/*~
	@rm -vf $(SRCDIR)/display/*~	
	@rm -vf $(BENCH_DIR)/*~
	@rm -vf *~ *.o *.out *.so
	@rm -vf *.ll 
	@rm -vf \#*\#

%.ll: %.c
	$(CLANG) $<










