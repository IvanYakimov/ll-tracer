#include "string-support.hpp"

namespace trans {
  using namespace llvm;
  StringSupport::StringSupport(Module& module, std::string prefix) : module_(module), prefix_(prefix) {
    //  abort(); // no module_ initialization;
  }
  
  Constant* StringSupport::LazyMemoBuff(CString buffer) {
    auto target = std::string(buffer);
    auto it = buffer_table_.find(target);
    std::cout << "ON " << buffer;
    if (it != buffer_table_.end()) {
      std::cout << " MEMOIZE" << "\n";
      return it->second;
    } else {
      std::cout << " STORE" << "\n";
      auto charTy_ = IntegerType::getInt8Ty(module_.getContext());
      //auto intTy_ = IntegerType::getInt32Ty(module_.getContext());
      auto charPtrTy_ = IntegerType::getInt8PtrTy(module_.getContext());
      auto len = target.length() + 1;
      auto arr_ty = ArrayType::get(charTy_, len);
      GlobalVariable* str = new GlobalVariable(module_, arr_ty, true, GlobalValue::PrivateLinkage, 0, prefix_.c_str());
      str->setAlignment(1);
      Constant* str_data = ConstantDataArray::getString(module_.getContext(), buffer, true);
      str->setInitializer(str_data);
      GlobalVariable* str_ptr = new GlobalVariable(module_, charPtrTy_, false, GlobalValue::ExternalLinkage, 0, (prefix_ + "_ptr").c_str());
      str_ptr->setAlignment(8);
      std::vector<Constant*> str_ptr_indices;
      //TODO: replace StringRef("0") by number
      ConstantInt* zero = ConstantInt::get(module_.getContext(), APInt(32, 0, false));
      str_ptr_indices.push_back(zero);
      str_ptr_indices.push_back(zero);
      Constant* const_ptr = ConstantExpr::getGetElementPtr(str, str_ptr_indices);
      str_ptr->setInitializer(const_ptr);
      buffer_table_.emplace(target, str_ptr);
      return str_ptr;
    }
  }
}
