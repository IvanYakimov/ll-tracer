// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __ENGINE__
#define __ENGINE__

#include <iostream>
#include <string>
#include <memory>

// project:
#include "declarations.hpp"
#include "printer-factory.hpp"
#include "frame-stack.hpp"

namespace engine {
  class Engine;
  using EnginePtr = std::shared_ptr<Engine>;
  EnginePtr GetEngine();
  class Engine {
    PrinterFactory factory_;
    FrameStack stack_;
  public:
    void Alloca(Pointer pointer, const char* type_specifier);
    void Return();
    void Call();
    void BlockEnd();
  };
};

#endif
