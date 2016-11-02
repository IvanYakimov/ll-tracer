#include "tracer-pass.hpp"

bool TracerPass::runOnModule(llvm::Module &module) {
  trans::Transformer tr(module);
  tr.visit(module);
  llvm::errs().flush();
  llvm::errs() << module;
  // some transformations done
  return true;
}
