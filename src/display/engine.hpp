// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __ENGINE__
#define __ENGINE__

#include <iostream>
#include <string>

namespace engine {
  class Engine {
  public:
    static void Alloca(long *pointer, std::string type_specifier);
    static void Return();
    static void Call();
    static void BlockEnd();
  };
};

#endif
