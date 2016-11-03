// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "c-driver.hpp"

extern "C" {
  void alloca_handler(long* pointer, int type_specifier) {
    cpp__alloca_handler(pointer, type_specifier);
  }
}

void cpp__alloca_handler(long *pointer, int type_specifier) {
  engine::Engine::Alloca(pointer, type_specifier);
}

