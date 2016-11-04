// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __TRANSFORMER__
#define __TRANSFORMER__

// project
#include "transformer_helper.hpp"

namespace trans {
  class Transformer : public llvm::InstVisitor<Transformer>, public TransformerHelper {
  public:
    Transformer(llvm::Module &module);
    ~Transformer();
    void visitAllocaInst(llvm::AllocaInst &alloca);
    
  private:
    const char* kAlloca_ = "alloca_handler";
    llvm::Constant* LazySpecification(llvm::Type* ty);
    void DeclareAlloca();
  };
};

#endif
