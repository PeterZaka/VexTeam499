#pragma once

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