#pragma once

/*

- Use smart pointers from <memory>
- Too much work for something that barely helped
it's easier to write if(button) motor.power(100);

*/

#include "motorGroup.h"

namespace team499 {

  class input
  {
  public:

    input(
      bool (*inputFunc)(),
      const std::vector<motorGroup*>& positiveGroups,
      const std::vector<motorGroup*>& negativeGroups = {});

    void Update();


  private:

    bool (*inputFunc)();
    std::vector<motorGroup*> positiveGroups;
    std::vector<motorGroup*> negativeGroups;
  };

  // Gearshift

	extern double gearShiftPower;
	extern bool changedGearShift;

	double GetGearShiftPower();

	void updateGearShift();

}