#pragma once

#include "vex.h"

namespace team499 {

  void resetScreen();

  template<typename T>
  void printOnController(std::string name, T t)
  {
    Controller1.Screen.print("%s: %.2lf", name.c_str(), (double)t);
    Controller1.Screen.newLine();
  }

  void printOnController(std::string name);

  double quickestRotation(double currentRot, double target);


  // MATH

  double posMod(double n, double M);

  double roundToMultiple(double num, double multiple);

  double clamp(double num, double min, double max);
}