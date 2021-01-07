#include "input.h"

namespace team499 {

  double gearShiftPower = 30;
  bool changedGearShift;

  double roundToDigit(double number)
  {
    int n = number;
    int a = (n / 10) * 10;
    int b = a + 10;
    return (abs(n - a) > abs(b - n)) ? b : a;
  }

  double GetGearShiftPower()
  {
    return gearShiftPower;
  }

  void updateGearShift()
  {
    if (Controller1.ButtonY.pressing() || Controller1.ButtonRight.pressing())
    {
      if (!changedGearShift)
      {
        if (Controller1.ButtonY.pressing())
        {
          gearShiftPower += 10;
        }
        else
        {
          gearShiftPower -= 10;
        }
        changedGearShift = true;
      }
    }
    else
    {
      changedGearShift = false;
    }
  }

  void printGearShift()
  {
    Controller1.Screen.setCursor(0, 0);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Power: %.lf", gearShiftPower);
    //Controller1.Screen.setCursor(0, 2);
    Controller1.Screen.newLine();
    Controller1.Screen.print("Velocity: %.2lf",
      flywheelLeft.velocity(pct) +
      flywheelRight.velocity(pct) / 2);
  }

  void printThis(float thing)
  {
    Controller1.Screen.newLine();
    //printf("%.2lf\n", thing);
    Controller1.Screen.print("%.2lf", thing);
  }
}