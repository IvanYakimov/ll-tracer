// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __C_DRIVER__
#define __C_DRIVER__

#include <string>
#include "engine.hpp"

extern "C" {
  void alloca_handler(long* pointer, char* type_specifier);
  void return_handler();
  void call_handler();
  void block_handler();
}

void cpp__alloca_handler(long *pointer, char* type_specifier);
void cpp__return_handler();
void cpp__call_handler();
void cpp__block_handler();

#endif
