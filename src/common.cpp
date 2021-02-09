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

      if(Controller1.ButtonB.pressing())
      {
        printOnController("left", driveLeft.temperature(fahrenheit));
        printOnController("right", driveRight.temperature(fahrenheit));
      }
      else
      {
        printOnController("rot", rot);
        printOnController("target",targetRot);
      }

      wait(20, msec);
    }
  }

  double quickestRotation(double start, double target)
  {
    target = posMod(target, 360);
    //printf("\n\n\n\n\nstart: %.2lf\n", start);
    //printf("target: %.2lf\n", target);
    double roundedStart = roundToMultiple(start, 360);
    double val1 = roundedStart + target;
    double val2 = roundedStart - (360 - target);
    double val3 = val1 + 360;
    //printf("%.2lf, %.2lf, %.2lf\n", val1, val2, val3);
    if(fabs(val1 - start) < fabs(val2 - start) && fabs(val1 - start) < fabs(val3 - start))
    {
      //printf("val1: %.2lf\n\n", val1);
      return val1;
    }
    else if(fabs(val2 - start) < fabs(val3 - start))
    {
      //printf("val2: %.2lf\n\n", val2);
      return val2;
    }
    //printf("val3: %.2lf\n\n", val3);
    return val3;
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