#ifndef __STRING_SUPPORT__
#define __STRING_SUPPORT__

// LLVM
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"

// STL
#include <iostream>
#include <string>

// PROJECT


namespace trans {
  using CString = const char*;
  class StringSupport {
    using BuffMap = std::map<std::string, llvm::Constant*>;
    BuffMap buffer_table_;
    llvm::Module& module_;
    std::string prefix_;
  public:
    StringSupport(llvm::Module& module, std::string prefix_);
    // Lazy, memoized buffer allocation in the global memory
    // of the target module
    llvm::Constant* LazyMemoBuff(CString buffer);
  };
};

#endif
