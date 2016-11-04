// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __CONTROL_TRANSFORMER__
#define __CONTROL_TRANSFORMER__

// project
#include "transformer_helper.hpp"

namespace trans {
  class ControlTransformer : public llvm::InstVisitor<ControlTransformer>, public TransformerHelper {
  public:
    ControlTransformer(llvm::Module &module);
    ~ControlTransformer();

    void visitReturnInst(llvm::ReturnInst &ret);
    void visitCallInst(llvm::CallInst &call);
    void visitBasicBlock(llvm::BasicBlock &block);

  private:
    void helper(llvm::Instruction* target, const char* name);
    const char* kReturn_ = "return_handler";
    const char* kCall_ = "call_handler";
    const char* kBlock_ = "block_handler";
  };
};

#endif
