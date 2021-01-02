#include "toggleMotor.h"

// CONSTRUCTORS

toggleMotor::toggleMotor(std::string name, double defaultPower, const std::vector<vex::motor*>& motors) :
motorGroup(name, defaultPower, motors) {}

toggleMotor::toggleMotor(std::string name, double (*powerFunction)(), const std::vector<vex::motor*>& motors) :
motorGroup(name, powerFunction, motors) {}


// PRIVATE FUNCTIONS

void toggleMotor::Update()
{
  if(m_anyButtonPressed)
  {
    if(!m_anyButtonWasTrue)
    {
      m_isToggled = !m_isToggled;
      m_anyButtonWasTrue = true;
    }
  }
  else
  {
    m_anyButtonWasTrue = false;
  }
  m_currentPower *= m_isToggled;
  SpinMotorsAt(m_currentPower);
  m_anyButtonPressed = false;
}