#ifndef __TRANSFORMER_HELPER__
#define __TRANSFORMER_HELPER__

#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

namespace trans {
  class TransformerHelper {
  protected:
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

    llvm::Function* GetFunc(std::string name);
    void CreateFunc(std::string name, llvm::FunctionType* ty);
    void DeclareFunc(llvm::Type* ret, std::string name, FuncArgs fargs, bool variadic);
    
  public:
    TransformerHelper(llvm::Module &module);
    ~TransformerHelper();
  };
}
#endif
