#ifndef __FRAME_STACK__
#define __FRAME_STACK__

// STL
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <algorithm>

// Project
#include "declarations.hpp"
#include "printer.hpp"

namespace engine {
  class FrameStack {
    using Frame = std::map<Pointer, PrinterPtr>;
    using FramePtr = std::shared_ptr<Frame>;
    using TheStack = std::vector<FramePtr>;
    TheStack stack_;
  public:
    void Push();
    void Pop();
    void Emplace(Pointer, PrinterPtr);
    void PrintTop(std::ostream &file);
    bool IsEmpty();
  };
};

#endif
