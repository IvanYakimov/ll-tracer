#include "transformer.hpp"

namespace trans {
  using namespace llvm;
  using std::string;
  Transformer::Transformer(Module& module) : module_(module) {}

  Transformer::~Transformer() {}

  void Transformer::CreateFunc(string name, FunctionType* ty) {
    Function *func = Function::Create(ty, Function::ExternalLinkage, name.c_str(), &module_);
    func_table_.emplace(name, func);
  }

  void Transformer::DeclareFunc(Type* ret, string name, FuncArgs fargs, bool variadic) {
    FunctionType* ty = FunctionType::get(ret, fargs, variadic);
    CreateFunc(name, ty);
  }

  void Transformer::visitReturnInst(llvm::ReturnInst &return_inst) {
    errs() << "ret\n";
  }
  
  void Transformer::visitAllocaInst(llvm::AllocaInst &alloca) {
    errs() << "alloca\n";
  }
  
  void Transformer::visitCallInst(llvm::CallInst &call) {
    errs() << "call\n";
  }

  void Transformer::visitBasicBlock(llvm::BasicBlock &block) {
    errs() << "bb\n";
  }
};
