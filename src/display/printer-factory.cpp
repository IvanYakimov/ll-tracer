#include "printer-factory.hpp"

namespace engine {
  using namespace std;
  
  PrinterPtr PrinterFactory::ProducePrinter(CString type_specifier) {
    std::string target(type_specifier);
    if (std::regex_match(target, std::regex("i[[:digit:]]+"))) {
      //TODO: replace 'magical number' by some constant
      unsigned bitwidth;
      sscanf(type_specifier, "i%d", &bitwidth);
      //TODO: unsigned integers support
      std::cout << "Integer matched: i" << bitwidth << std::endl;
      switch(bitwidth) {
      case 8:
	return make_shared<IntPrinter<char>>();
      case 16:
	return make_shared<IntPrinter<short>>();
      case 32:
	return make_shared<IntPrinter<int>>();
      case 64:
	return make_shared<IntPrinter<long>>();
      default:
	std::cerr << "bad bitwidth " << bitwidth << std::endl;
	assert ("bad bitwidth" and false);
      }
    } else if (std::regex_match(target, std::regex("[[[:digit:]]+ x i[[:digit:]]+]"))) {
      //assert (not "implemented");
      size_t length;
      int bitwidth;
      sscanf(type_specifier, "[%d x i%d]", &length, &bitwidth);
      std::cout << "Array matched: [" << length << " x i" << bitwidth << "]" << std::endl;
      //TODO: make a template (maybe with help of functors)
      switch(bitwidth) {
      case 8:
	return make_shared<ArrayPrinter<char>>(length);
      case 16:
	return make_shared<ArrayPrinter<short>>(length);
      case 32:
	return make_shared<ArrayPrinter<int>>(length);
      case 64:
	return make_shared<ArrayPrinter<long>>(length);
      default:
	std::cerr << "bad bitwidth " << bitwidth << std::endl;
	assert ("bad bitwidth" and false);
      }
      return nullptr;
    } else {
      assert (not "implemented");
    }
  }
  
  PrinterPtr PrinterFactory::GetPrinter(CString type_spec) {
    auto it = printer_table_.find(type_spec);
    if (it != printer_table_.end()) {
      return it->second;
    } else {
      auto printer = ProducePrinter(type_spec);
      printer_table_.emplace(type_spec, printer);
      return printer;
    }
  }
};
