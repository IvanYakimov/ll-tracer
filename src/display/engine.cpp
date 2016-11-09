// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "engine.hpp"

namespace engine {
  Engine::Engine() {
    stack_.Push();
  }

  Engine::~Engine() {
    assert (stack_.IsEmpty());
  }
  
  EnginePtr GetEngine() {
    static EnginePtr engine = nullptr;
    if (engine == nullptr)
      engine = std::make_shared<Engine>();
    return engine;
  }
  
  void Engine::Alloca(Pointer pointer, const char* type_specifier) {
    assert (pointer not_eq nullptr
	    and type_specifier not_eq nullptr);
    auto printer = factory_.GetPrinter(type_specifier);
    assert (printer not_eq nullptr);
    stack_.Emplace(pointer, printer);
  }

  void Engine::Return() {
    stack_.Pop();
  }
  
  void Engine::Call() {
    stack_.Push();
  }
  
  void Engine::BlockEnd() {
    stack_.PrintTop(std::cout);
    std::cout << std::endl;
  }
};
