// Copyright 2016 Ivan Yakimov
// Licensed under the Apache License, Version 2.0
// e-mail: ivan.yakimov.research@yandex.ru

#include "transformer.hpp"

namespace trans {
  using namespace llvm;
  using std::string;
  AllocaTransformer::AllocaTransformer(Module& module) : TransformerHelper(module) {
    // Declare functions
    DeclareFunc(voidTy_, kAlloca_, {longPtrTy_, charPtrTy_}, kNotVariadic_);
  }

  AllocaTransformer::~AllocaTransformer() {}

  llvm::Constant* AllocaTransformer::LazySpecification(llvm::Type* allocated_type) {
    string buffer;
    raw_string_ostream type_ss(buffer);
    type_ss << *allocated_type;
    auto type_str = type_ss.str();
    auto it = spec_table_.find(type_str);
    if (it != spec_table_.end()) {
      return it->second;
    } else {
      auto len = type_str.length() + 1;
      auto arr_ty = ArrayType::get(charTy_, len);
      GlobalVariable* gvar_array_str = new GlobalVariable(module_, arr_ty, true, GlobalValue::PrivateLinkage, 0, "ty_spec_");
      gvar_array_str->setAlignment(1);
      Constant* const_array = ConstantDataArray::getString(module_.getContext(), type_str.c_str(), true);
      gvar_array_str->setInitializer(const_array);
      GlobalVariable* gvar_ptr = new GlobalVariable(module_, charPtrTy_, false, GlobalValue::ExternalLinkage, 0, "ty_spec_ptr_");
      gvar_ptr->setAlignment(8);
      std::vector<Constant*> const_ptr_indices;
      //TODO: replace StringRef("0") by number
      ConstantInt* zero = ConstantInt::get(module_.getContext(), APInt(32, StringRef("0"), 10));
      const_ptr_indices.push_back(zero);
      const_ptr_indices.push_back(zero);
      Constant* const_ptr = ConstantExpr::getGetElementPtr(gvar_array_str, const_ptr_indices);
      gvar_ptr->setInitializer(const_ptr);
      spec_table_.emplace(type_str, gvar_ptr);
      return gvar_ptr;
    }
  }
  
  void AllocaTransformer::visitAllocaInst(llvm::AllocaInst &alloca) {
    Type* allocated_type = alloca.getAllocatedType();
    bool isInt = allocated_type->isIntegerTy(),
      isArr = allocated_type->isArrayTy();

    // Only integers and arrays are under monitoring
    if (not (isInt or isArr))
      return;

    // TODO: GetFunc rename to GetHandler, which should obtain Instruction& as an argument
    auto handler = GetFunc(kAlloca_);
    auto spec = LazySpecification(allocated_type);
    assert (spec not_eq nullptr);
    Instruction *cast = new BitCastInst(&alloca, longPtrTy_);
    cast->insertAfter(&alloca);
    Instruction *load = new LoadInst(spec);
    load->insertAfter(cast);
    FuncOps ops = {cast, load};
    Instruction *call = CallInst::Create(handler, ops);
    call->insertAfter(load);
  }
};
