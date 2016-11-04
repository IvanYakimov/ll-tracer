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
    charPtrTy_ = Type::getInt8PtrTy(context);
    shortTy_ = Type::getInt16Ty(context);
    intTy_ = Type::getInt32Ty(context);
    longTy_ = Type::getInt64Ty(context);
    longPtrTy_ = Type::getInt64PtrTy(context);

    // Init mappings
    auto init_spec = [=] (TypeSpec id) {
      auto spec = ConstantInt::get(intTy_, (int)id, kNotSigned_);
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
  }

  void Transformer::DeclareAlloca() {
    Type* ptr = longPtrTy_,
      * tag = intTy_,
      * format = charPtrTy_;
    DeclareFunc(voidTy_, kAlloca_, {ptr, tag}, kNotVariadic_);
  }
  
  void Transformer::DeclarePush() {
    
  }
  
  void Transformer::DeclarePop() {
    
  }

  void Transformer::visitReturnInst(llvm::ReturnInst &return_inst) {
  }
  
  void Transformer::visitAllocaInst(llvm::AllocaInst &alloca) {
    Type* allocated_type = alloca.getAllocatedType();
    bool isInt = allocated_type->isIntegerTy(),
      isArr = allocated_type->isArrayTy();

    if (not (isInt or isArr))
      return;

    if (allocated_type->isIntegerTy()) {
      auto handler = GetFunc(kAlloca_);
      auto spec = GetSpec(allocated_type);
      Constant* addr = ConstantInt::get(longTy_, 42, kNotSigned_);
      Instruction* cast = new BitCastInst(&alloca, longPtrTy_);
      cast->insertAfter(&alloca);
      FuncOps ops = {cast, spec};
      Instruction* call = CallInst::Create(handler, ops);
      call->insertAfter(cast);
    }
    else if (allocated_type->isArrayTy()) {
      string buffer;
      raw_string_ostream type_ss(buffer);
      type_ss << *allocated_type;
      auto type_str = type_ss.str();
      //      errs() << "ARRAY INITIALIZER: " << buffer.c_str() << "\n";
      //TODO: lazy initialization (+ memoization):
      auto len = type_str.length() + 1;
      errs() << "STR: " << type_str << "\n";
      errs() << "LEN: " << len << "\n";
      auto arr_ty = ArrayType::get(charTy_, len);
      GlobalVariable* gvar_array_str = new GlobalVariable(module_, arr_ty, true, GlobalValue::PrivateLinkage, 0, ".str");
      gvar_array_str->setAlignment(1);
      Constant* const_array = ConstantDataArray::getString(module_.getContext(), type_str.c_str(), true);
      gvar_array_str->setInitializer(const_array);
      GlobalVariable* gvar_ptr = new GlobalVariable(module_, charPtrTy_, false, GlobalValue::ExternalLinkage, 0, "buff");
      gvar_ptr->setAlignment(8);
      std::vector<Constant*> const_ptr_indices;
      ConstantInt* zero = ConstantInt::get(module_.getContext(), APInt(32, StringRef("0"), 10));
      const_ptr_indices.push_back(zero);
      const_ptr_indices.push_back(zero);
      Constant* const_ptr = ConstantExpr::getGetElementPtr(gvar_array_str, const_ptr_indices);
      gvar_ptr->setInitializer(const_ptr);
      //errs() << rso.str().c_str() << "\n";
      //TODO:
    }
  }
  
  void Transformer::visitCallInst(llvm::CallInst &call) {
  }

  void Transformer::visitBasicBlock(llvm::BasicBlock &block) {
  }
};
