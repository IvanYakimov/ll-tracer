#include "frame-stack.hpp"

namespace engine {
  bool FrameStack::IsEmpty() {
    return stack_.empty();
  }
  
  void FrameStack::Push() {
    stack_.push_back(std::make_shared<Frame>());
  }

  void FrameStack::Pop() {
    stack_.pop_back();
  }

  void FrameStack::Emplace(Pointer ptr, PrinterPtr printer) {
    assert (ptr not_eq nullptr and printer not_eq nullptr);
    auto top = stack_.back();
    assert (top->find(ptr) == top->end() and "pointer must be unique");
    top->emplace(ptr, printer);
  }

  void FrameStack::PrintTop(std::ostream &file) {
    for (auto it = stack_.begin(); it != stack_.end(); it++) {
      auto top = *it;
      file << " #frame " << it - stack_.begin() << ": ";
    std::for_each(top->begin(), top->end(), [&] (auto item) {
	Pointer ptr = item.first;
	PrinterPtr printer = item.second;
	assert (ptr not_eq nullptr and printer not_eq nullptr);
	printer->Print(file, ptr);
	;});
    }
  }
};
