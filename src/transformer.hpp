#ifndef __TRANSFORMER__
#define __TRANSFORMER__

#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

enum class TypeSpec{
    kI8Ty,
    kI16Ty,
    kI32Ty,
    kI64Ty,
    kArray,
    kStruct
};

namespace trans {
  class Transformer : public llvm::InstVisitor<Transformer> {
  private:
    using FuncTable = std::map<std::string, llvm::Function*>;
    using FuncArgs = std::vector<llvm::Type*>;

    llvm::Module& module_;
    FuncTable func_table_;
    
    void CreateFunc(std::string name, llvm::FunctionType* ty);
    void DeclareFunc(llvm::Type* ret, std::string name, FuncArgs fargs, bool variadic);
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
