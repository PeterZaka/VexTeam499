#pragma once

#include "vex.h"

namespace team499 {

	double roundToDigit(double number);

  void resetScreen();

  template<typename T>
  void printOnController(std::string name, T t)
  {
    Controller1.Screen.print("%s: %g", name.c_str(), (double)t);
    Controller1.Screen.newLine();
  }

  void printOnController(std::string name);
}