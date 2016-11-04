// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#ifndef __TRANSFORMER__
#define __TRANSFORMER__

#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

namespace trans {
  class Transformer : public llvm::InstVisitor<Transformer> {
  private:
    using FuncTable = std::map<std::string, llvm::Function*>;
    using SpecMap = std::map<std::string, llvm::Constant*>;
    using FuncArgs = std::vector<llvm::Type*>;
    using FuncOps = std::vector<llvm::Value*>;

    llvm::Module& module_;
    FuncTable func_table_;
    SpecMap spec_table_;

    llvm::Type* voidTy_;
    llvm::Type* boolTy_;
    llvm::Type* charTy_;
    llvm::Type* charPtrTy_;
    llvm::Type* shortTy_;
    llvm::Type* intTy_;
    llvm::Type* longTy_;
    llvm::Type* longPtrTy_;
    const bool kVariadic_ = true;
    const bool kNotVariadic_ = false;
    const bool kNotSigned_ = false;
    const char* kAlloca_ = "alloca_handler";

    llvm::Function* GetFunc(std::string name);
    llvm::Constant* LazySpecification(llvm::Type* ty);
    void CreateFunc(std::string name, llvm::FunctionType* ty);
    void DeclareFunc(llvm::Type* ret, std::string name, FuncArgs fargs, bool variadic);
    llvm::Value* Instrument(llvm::Instruction* target, llvm::Function* func, FuncOps ops);
    
    void DeclareAlloca();
    void DeclarePush();
    void DeclarePop();
    
  public:
    Transformer(llvm::Module &module);
    ~Transformer();
    void visitReturnInst(llvm::ReturnInst &return_inst);
    void visitAllocaInst(llvm::AllocaInst &alloca);
    void visitCallInst(llvm::CallInst &call);
    void visitBasicBlock(llvm::BasicBlock &block);
  };
};

#endif
