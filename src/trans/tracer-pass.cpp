#include "tracer-pass.hpp"

bool TracerPass::runOnModule(llvm::Module &module) {
  trans::Transformer tr(module);
  tr.visit(module);
  std::string err;
  llvm::raw_fd_ostream outfile("dummy.ll", err, llvm::sys::fs::OpenFlags::F_RW);
  outfile << module;
  // some transformations done
  return true;
}
