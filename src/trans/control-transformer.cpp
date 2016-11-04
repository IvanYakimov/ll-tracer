// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "control-transformer.hpp"

namespace trans {
  using namespace llvm;
  using std::string;
  ControlTransformer::ControlTransformer(llvm::Module &module) : TransformerHelper(module) {
    DeclareFunc(voidTy_, kReturn_, {}, kNotVariadic_);
    DeclareFunc(voidTy_, kCall_, {}, kNotVariadic_);
    DeclareFunc(voidTy_, kBlock_, {}, kNotVariadic_);
  }

  ControlTransformer::~ControlTransformer() {}

  void ControlTransformer::helper(llvm::Instruction* target, const char* name) {
    auto handler = GetFunc(name);
    IRBuilder<> builder(target);
    FuncOps ops = {};
    builder.CreateCall(handler, ops);
  }

  void ControlTransformer::visitReturnInst(llvm::ReturnInst &ret) {
    helper(&ret, kReturn_);
  }
  
  void ControlTransformer::visitCallInst(llvm::CallInst &call) {
      auto callee = call.getCalledFunction();
      StringRef name_ref = callee->getName();
      std::string name = name_ref.str();
      //TODO: improve this ugly method of 'built-ins' checking
      if (name != "block_handler" and name != "return_handler" and name != "call_handler" and name != "alloca_handler"
	  and name.substr(0,5) != "llvm.")
	helper(&call, kCall_);
  }
  
  void ControlTransformer::visitBasicBlock(llvm::BasicBlock &block) {
    auto handler = GetFunc(kBlock_);
    FuncOps ops = {};
    //    Instruction *call = CallInst::Create(handler, ops);
    auto last_instr = block.rbegin();
    IRBuilder<> builder (&*last_instr);
    builder.CreateCall(handler, ops);
  }

}
