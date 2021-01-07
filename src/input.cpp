#include "input.h"

namespace team499 {

  input::input(
    bool(*inputFunc)(),
    const std::vector<motorGroup*>& positiveGroups,
    const std::vector<motorGroup*>& negativeGroups)
    :
    inputFunc(inputFunc),
    positiveGroups(positiveGroups),
    negativeGroups(negativeGroups)
  {}

  void input::Update()
  {
    //printf("%d\n",inputFunc());
    if (inputFunc())
    {
      for (auto mg : positiveGroups)
      {
        mg->PositiveActivate();
      }
      for (auto mg : negativeGroups)
      {
        mg->NegativeActivate();
      }
    }
  }

  // Gearshift

  double gearShiftPower = 30;
  bool changedGearShift;

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

}