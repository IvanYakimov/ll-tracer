// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "engine.hpp"

namespace engine {
  void Engine::Alloca(long *pointer, int type_specifier) {
    if (type_specifier == 32) {
      int* val = (int*)pointer;
      std::cout << "allocated: " << *val << "\n";
    }
    else if (type_specifier == 65) {
      std::cout << "allocated array\n";
    }
  }
};
