// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __ENGINE__
#define __ENGINE__

#include <iostream>

namespace engine {
  class Engine {
  public:
    static void Alloca(long *pointer, int type_specifier);
  };
};

#endif
