#pragma once

#include "motorGroup.h"
#include "vex.h"

class toggleMotor : public motorGroup
{

	friend class controllerInput;

public:

  // CONSTRUCTORS
  toggleMotor(std::string name, double defaultPower, std::vector<vex::motor*> const& motors);
  toggleMotor(std::string name, double (*powerFunction)(), std::vector<vex::motor*> const& motors);


private:

  void Update() override;

  // toggles during update cycle
  bool m_isToggled = false;
  
  bool m_anyButtonWasTrue = false;

};