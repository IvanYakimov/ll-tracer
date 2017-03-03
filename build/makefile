# Copyright 2016 Ivan Yakimov
# Licensed under the Apache License, Version 2.0
# e-mail: ivan.yakimov.research@yandex.ru

SHELL = /bin/bash

SRCDIR = ../src

BENCH_C = $(shell cd $(BENCH_DIR) && ls *.c)
BENCH_IR = $(BENCH_C:.c=.ll)

DISPLAY_SRC = $(shell cd $(SRCDIR)/display && ls *.cpp)
DISPLAY = $(DISPLAY_SRC:.cpp=.o)

TRANS_SRC = $(shell cd $(SRCDIR)/trans && ls *.cpp)
TRANSFORMER = $(TRANS_SRC:.cpp=.o)

OBJ = $(ENGINE) $(TRANSFORMER)

CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g -std=c++1y -fpic -rdynamic -Wno-deprecated
LDFLAGS = 
LLVM_CXXDYNAMIC = $(filter-out -g -fno-exceptions -O2 -std=c++11, $(shell llvm-config --cxxflags))
LLVM_LDDYNAMIC = $(shell llvm-config --ldflags)
DBGFLAGS = -U NDEBUG

vpath %.cpp $(SRCDIR)/display $(SRCDIR)/trans

transformer.so: trans.o
	$(CXX) -shared $< -o $@ $(CXXFLAGS)

driver.a: $(DISPLAY)
	ar rcs $@ $^

trans.o: $(TRANSFORMER) 
	ld -r $^ -o $@ $(LLVM_LDDYNAMIC)

trans.out: $(TRANSFORMER)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LLVM_CXXDYNAMIC) 

$(OBJ):
%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	@rm -vf $(SRCDIR)/trans/*~
	@rm -vf $(SRCDIR)/display/*~	
	@rm -vf *~ *.o *.out *.so
	@rm -vf \#*\#
