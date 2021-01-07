#include "common.h"

namespace team499 {

  double roundToDigit(double number)
  {
    int n = number;
    int a = (n / 10) * 10;
    int b = a + 10;
    return (abs(n - a) > abs(b - n)) ? b : a;
  }

  void resetScreen()
  {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0, 0);
  }

  void printOnController(std::string name)
  {
    Controller1.Screen.print(name);
    Controller1.Screen.newLine();
  }
}