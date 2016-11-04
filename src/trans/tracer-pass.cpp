#include "tracer-pass.hpp"

bool TracerPass::runOnModule(llvm::Module &module) {
  trans::AllocaTransformer alloca_tr(module);
  trans::ControlTransformer control_tr(module);
  control_tr.visit(module);
  alloca_tr.visit(module);
  std::string err;
  llvm::raw_fd_ostream outfile("dummy.ll", err, llvm::sys::fs::OpenFlags::F_RW);
  outfile << module;
  // some transformations done
  return true;
}
