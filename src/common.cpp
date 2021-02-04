#include "common.h"

namespace team499 {

  void resetScreen()
  {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0, 0);
  }

  void printOnController(std::string name)
  {
    Controller1.Screen.print(name.c_str());
    Controller1.Screen.newLine();
    wait(5, msec);
  }

  void runPrints()
  {
    while(1)
    {
      resetScreen();

      printOnController("time", timer::system() - prevTime);

      if(Controller1.ButtonB.pressing())
      {
        printOnController("left", driveLeft.temperature(fahrenheit));
        printOnController("right", driveRight.temperature(fahrenheit));
      }

      wait(20, msec);
    }
  }

  double quickestRotation(double start, double target)
  {
    target = posMod(target, 360);
    double leftTurn = roundToMultiple(start, 360) + (target - 360);
    double rightTurn = roundToMultiple(start, 360) + target;
    return fabs(start - leftTurn) < fabs(start - rightTurn) ? leftTurn : rightTurn;
  }

  // MATH

  double posMod(double n, double M)
  {
    return fmod(fmod(n, M) + M, M);
  }

  double roundToMultiple(double num, double multiple)
  {
    int isPositive = 1;
    if (num < 0)
    {
      isPositive = -1;
      num *= -1;
    }
    if(fmod(num, multiple) /multiple > 0.5)
    {
      return ceil(num / multiple) * multiple * isPositive;
    }
    return floor(num / multiple) * multiple * isPositive;
  }

  double clamp(double num, double min, double max)
  {
    return std::max(min, std::min(num, max));
  }

  double limitDecimal(double num, double decimalPlace)
  {
    return (int)(num * pow(10,decimalPlace)) / pow(10,decimalPlace);
  }
}