#include "SmartPointer.hpp"
#include "Pointers.hpp"
#include <assert.h>

namespace SmartPtrNames {
  void printAllCounts(string str) {
    Pointers::getInstance()->print(str);
  }
}

