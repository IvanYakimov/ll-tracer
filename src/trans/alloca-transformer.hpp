// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __ALLOCA_TRANSFORMER__
#define __ALLOCA_TRANSFORMER__

// project
#include "transformer_helper.hpp"

namespace trans {
  class AllocaTransformer : public llvm::InstVisitor<AllocaTransformer>, public TransformerHelper {
  public:
    AllocaTransformer(llvm::Module &module);
    ~AllocaTransformer();
    void visitAllocaInst(llvm::AllocaInst &alloca);
    
  private:
    const char* kAlloca_ = "alloca_handler";
    //TODO: not only lazy, but singleton!
    llvm::Constant* LazySpecification(llvm::Type* ty);
  };
};

#endif
