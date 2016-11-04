// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "engine.hpp"

namespace engine {
  void Engine::Alloca(long *pointer, std::string type_specifier) {     
    std::cout << "allocated: " << type_specifier << "\n";
  }
};
