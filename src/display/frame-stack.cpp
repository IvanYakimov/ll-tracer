#include "frame-stack.hpp"

namespace engine {
  bool FrameStack::IsEmpty() {
    return stack_.empty();
  }
  
  void FrameStack::Push() {
    stack_.push(std::make_shared<Frame>());
  }

  void FrameStack::Pop() {
    stack_.pop();
  }

  void FrameStack::Emplace(Pointer ptr, PrinterPtr printer) {
    assert (ptr not_eq nullptr and printer not_eq nullptr);
    auto top = stack_.top();
    assert (top->find(ptr) == top->end() and "pointer must be unique");
    top->emplace(ptr, printer);
  }

  void FrameStack::PrintTop(std::ostream &file) {
    auto top = stack_.top();
    file << "printing: " << top->size() << std::endl;
    std::for_each(top->begin(), top->end(), [&] (auto item) {
	Pointer ptr = item.first;
	PrinterPtr printer = item.second;
	assert (ptr not_eq nullptr and printer not_eq nullptr);
	printer->Print(file, ptr);
	;});
  }
};
