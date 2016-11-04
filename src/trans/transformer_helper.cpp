#include "transformer_helper.hpp"

namespace trans {
  using namespace llvm;
  using std::string;
  TransformerHelper::TransformerHelper(Module& module) : module_(module) {
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
  }

  TransformerHelper::~TransformerHelper() {}
  
  Function* TransformerHelper::GetFunc(std::string name) {
    // make template
    auto it = func_table_.find(name);
    assert (it != func_table_.end());
    return it->second;
  }

  void TransformerHelper::CreateFunc(string name, FunctionType* ty) {
    Function *func = Function::Create(ty, Function::ExternalLinkage, name.c_str(), &module_);
    func_table_.emplace(name, func);
  }

  void TransformerHelper::DeclareFunc(Type* ret, string name, FuncArgs fargs, bool variadic) {
    FunctionType* ty = FunctionType::get(ret, fargs, variadic);
    CreateFunc(name, ty);
  }

};
