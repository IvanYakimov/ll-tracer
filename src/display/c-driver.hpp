// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __C_DRIVER__
#define __C_DRIVER__

#include <string>
#include "engine.hpp"

extern "C" {
  void alloca_handler(long* pointer, char* type_specifier);
}

void cpp__alloca_handler(long *pointer, char* type_specifier);

#endif
