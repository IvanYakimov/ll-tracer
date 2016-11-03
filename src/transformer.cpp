// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "transformer.hpp"

namespace trans {
  using namespace llvm;
  using std::string;
  Transformer::Transformer(Module& module) : module_(module) {
    // Init types
    LLVMContext& context = module_.getContext();
    voidTy_ = Type::getVoidTy(context);
    boolTy_ = Type::getInt1Ty(context);
    charTy_ = Type::getInt8Ty(context);
    shortTy_ = Type::getInt16Ty(context);
    intTy_ = Type::getInt32Ty(context);
    longTy_ = Type::getInt64Ty(context);
    strTy_ = Type::getInt8PtrTy(context);

    // Init mappings
    auto init_spec = [=] (TypeSpec id) {
      auto spec = ConstantInt::get(intTy_, (int)id, kNotSigned);
      spec_table_.emplace(id, spec);
    };
    std::vector<TypeSpec> spec_arr = {TypeSpec::kI8Ty, TypeSpec::kI16Ty, TypeSpec::kI32Ty, TypeSpec::kI64Ty,
				      TypeSpec::kArray, TypeSpec::kStruct};
    for_each(spec_arr.begin(), spec_arr.end(), [=](TypeSpec s){init_spec(s);});

    // Declare functions
    DeclareAlloca();
  }

  Transformer::~Transformer() {}

  Constant* Transformer::GetSpec(Type* ty) {
    // make template
    TypeSpec id;
    if (ty->isIntegerTy()) {
      auto width = ty->getIntegerBitWidth();
      id = (TypeSpec)width;
    }
    else if (ty->isArrayTy()) {
      id = TypeSpec::kArray;
    }
    else
      assert (not "implemented");
    
    auto it = spec_table_.find(id);
    assert (it != spec_table_.end());
    return it->second;
  }
  
  Function* Transformer::GetFunc(std::string name) {
    // make template
    auto it = func_table_.find(name);
    assert (it != func_table_.end());
    return it->second;
  }

  void Transformer::CreateFunc(string name, FunctionType* ty) {
    Function *func = Function::Create(ty, Function::ExternalLinkage, name.c_str(), &module_);
    func_table_.emplace(name, func);
  }

  void Transformer::DeclareFunc(Type* ret, string name, FuncArgs fargs, bool variadic) {
    FunctionType* ty = FunctionType::get(ret, fargs, variadic);
    CreateFunc(name, ty);
  }

  Value* Transformer::Instrument(Instruction* target, Function* func, FuncOps ops) {
    //errs() << target << "\n";
    Instruction* call = CallInst::Create(func, ops);
    call->insertAfter(target);
  }

  void Transformer::DeclareAlloca() {
    DeclareFunc(voidTy_, kAlloca, {intTy_}, kVariadic_);
  }
  
  void Transformer::DeclarePush() {
    
  }
  
  void Transformer::DeclarePop() {
    
  }

  void Transformer::visitReturnInst(llvm::ReturnInst &return_inst) {
    errs() << "ret\n";
  }
  
  void Transformer::visitAllocaInst(llvm::AllocaInst &alloca) {
    errs() << "alloca\n";
    string target;
    raw_string_ostream rso(target);
    Type* allocated_type = alloca.getAllocatedType();
    if (allocated_type->isIntegerTy()) {
      auto spec = GetSpec(allocated_type);
      auto func = GetFunc(kAlloca);
      FuncOps ops = {spec, &alloca};
      Instrument(&alloca, func, ops);
    }
    else if (allocated_type->isArrayTy()) {
      auto spec = GetSpec(allocated_type);
      auto func = GetFunc(kAlloca);
      FuncOps ops = {spec};
      rso << *allocated_type;
      errs() << rso.str().c_str() << "\n";
    }
  }
  
  void Transformer::visitCallInst(llvm::CallInst &call) {
    errs() << "call\n";
  }

  void Transformer::visitBasicBlock(llvm::BasicBlock &block) {
    errs() << "bb\n";
  }
};
