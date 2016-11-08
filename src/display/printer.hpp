#ifndef __PRINTER__
#define __PRINTER__

#include <vector>
#include <iostream>
#include <cstring>
#include <memory>

// project:
#include "declarations.hpp"

namespace engine {
  class Printer;
  using PrinterPtr = std::shared_ptr<Printer>;

  class Printer {
    virtual void Print(std::ostream& file, Pointer pointer) = 0;
  };
  
  template<typename T>
  struct IntPrinter final : public Printer {
    virtual void Print(std::ostream& file, Pointer pointer) {
      T val;
      std::memcpy(&val, pointer, sizeof(T));
      file << val;
    }
  };

  template<typename T>
  struct ArrayPrinter final : public Printer {
    size_t n;
    ArrayPrinter(unsigned length) : n(length){}
    virtual void Print(std::ostream& file, Pointer pointer) {
      T buff[n];
      std::memcpy(&buff, pointer, sizeof(buff));
      file << "{";
      for (int i = 0; i < n; i++) {
	file << buff[i];
	if (i < i-1)
	  file << ",";
      }
      file << "}";
    };
  };

  struct MatrixPrinter final : public Printer {
    //TODO: n-dimensional array support
  };
};

#endif
