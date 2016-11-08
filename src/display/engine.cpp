// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "engine.hpp"

namespace engine {
  EnginePtr GetEngine() {
    static EnginePtr engine = nullptr;
    if (engine == nullptr)
      engine = std::make_shared<Engine>();
    return engine;
  }
  
  void Engine::Alloca(long *pointer, const char* type_specifier) {
    auto printer = factory_.GetPrinter(type_specifier);
  }

  void Engine::Return() {
  }
  
  void Engine::Call() {
  }
  
  void Engine::BlockEnd() {
  }
};
