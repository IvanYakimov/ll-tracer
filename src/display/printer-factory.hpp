#ifndef __PRINTER_FACTORY__
#define __PRINTER_FACTORY__

// standard library:
#include <map>
#include <regex>
#include <iostream>
#include <cassert>

// project:
#include "declarations.hpp"
#include "printer.hpp"

namespace engine {
  class PrinterFactory {
    using PrinterMap = std::map<CString, PrinterPtr>;
    PrinterMap printer_table_;
    PrinterPtr ProducePrinter(CString type_specifier);
  public:
    PrinterPtr GetPrinter(CString type_specifier);
  };
};

#endif
