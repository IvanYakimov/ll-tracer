#ifndef __PRINTER__
#define __PRINTER__

#include <vector>
#include <iostream>
#include <cstring>
#include <memory>
#include <cassert>

// project:
#include "declarations.hpp"

namespace engine {
  class Printer;
  using PrinterPtr = std::shared_ptr<Printer>;

  struct Printer {
    virtual void Print(std::ostream& file, Pointer pointer) = 0;
  };
  
  template<typename T>
  struct IntPrinter final : public Printer {
    virtual void Print(std::ostream& file, Pointer pointer) {
      //      T val;
      //std::memcpy(&val, pointer, sizeof(T));
      file << *((T*)pointer) << " ";
    }
  };

  template<typename T>
  struct ArrayPrinter final : public Printer {
    size_t n;
    ArrayPrinter(unsigned length) : n (length){}
    virtual void Print(std::ostream& file, Pointer pointer) {
      T *buff = (T*)pointer;
      //      std::memcpy(&buff, pointer, n);
      file << "{";
      for (int i = 0; i < n; i++) {
	file << buff[i];
	if (i < n-1)
	  file << ",";
      }
      file << "} ";
    };
  };

  struct MatrixPrinter final : public Printer {
    //TODO: n-dimensional array support
  };
};

#endif
