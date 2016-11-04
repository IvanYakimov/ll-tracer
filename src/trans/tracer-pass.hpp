#ifndef __TRACER_PASS__
#define __TRACER_PASS__

/// llvm
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

/// the project
#include "alloca-transformer.hpp"
#include "control-transformer.hpp"

#include <system_error>

namespace {
  struct TracerPass : public llvm::ModulePass {
    static char ID;
    TracerPass() : ModulePass(ID){}
    bool runOnModule(llvm::Module &module) override;
  };
};

char TracerPass::ID = 0;
static llvm::RegisterPass<TracerPass> X("ll-tracer", "llvm code dynamic tracer", false, false);

#endif
