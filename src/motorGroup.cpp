#include "motorGroup.h"

namespace team499 {

  // CONSTRUCTORS

  motorGroup::motorGroup(std::string name, double defaultPower, std::vector<vex::motor*> const& motors) :
    m_name(name), m_defaultPower(defaultPower), m_powerFunction(nullptr), m_motors(motors)
  {
    allMotorGroups.push_back(this);
  }

  motorGroup::motorGroup(std::string name, double (*powerFunction)(), std::vector<vex::motor*> const& motors) :
    m_name(name), m_defaultPower(0), m_powerFunction(powerFunction), m_motors(motors)
  {
    allMotorGroups.push_back(this);
  }


  // HELPER FUNCTIONS

  float motorGroup::AverageRotation() const
  {
    float averageRotationValue = 0;
    for (auto m : m_motors)
    {
      averageRotationValue += m->rotation(deg);
    }
    averageRotationValue /= m_motors.size();
    return averageRotationValue;
  }

  void motorGroup::ResetEncoders()
  {
    for (auto m : m_motors)
    {
      m->resetRotation();
    }
  }


  // AUTONOMOUS FUNCTIONS

  void motorGroup::SpinMotorsTo(double pow, double degrees)
  {
    ResetEncoders();
    for (auto m : m_motors)
    {
      m->startRotateTo(degrees, deg, pow, velocityUnits::pct);
    }
  }

  void motorGroup::Stop()
  {
    for (auto m: m_motors)
    {
      m->stop();
    }
  }

  void motorGroup::CorrectMotors(double degrees)
  {
    if (AverageRotation() < degrees)
    {
      while (fabs(AverageRotation() - degrees) > 10)
      {
        if (AverageRotation() > degrees)
        {
          SpinMotorsAt(-10);
        }
        else
        {
          SpinMotorsAt(10);
        }
      }
    }
    ResetEncoders();
  }

  void motorGroup::WaitUntilReaches(float degrees)
  {
    while (fabs(AverageRotation()) < fabs(degrees * 0.95))
    {
      wait(20, msec);
    }
  }


  // USERCONTROL FUNCTIONS

  void motorGroup::SpinMotorsAt(double const motorGroupPower) const
  {
    for (auto m : m_motors)
    {
      m->spin(fwd, motorGroupPower, pct);
    }
  }


  // MISC

  void motorGroup::PrintRotation()
  {
    if (fabs(m_motors[0]->velocity(pct)) < 5 && fabs(this->AverageRotation()) > 10)
    {
      printf("%s: %.2lf\n", m_name.c_str(), AverageRotation());
      this->ResetEncoders();
    }
  }

  void motorGroup::UpdateDefaultPower()
  {
    if (m_powerFunction != nullptr)
    {
      m_currentPower = m_powerFunction();
    }
  }


  // PRIVATE FUNCTIONS

  void motorGroup::PositiveActivate()
  {
    m_anyButtonPressed = true;
    m_currentPower = m_defaultPower;
  }

  void motorGroup::NegativeActivate()
  {
    m_anyButtonPressed = true;
    m_currentPower = -m_defaultPower;
  }


  void UpdateAllMotors()
  {
    for (auto mg : allMotorGroups)
    {
      mg->UpdateDefaultPower();
      mg->Update();
    }
  }

  void PrintWantedMotors()
  {
    for (auto mg : allMotorGroups)
    {
      mg->PrintRotation();
    }
  }

  void ResetAllMotorRotations()
  {
    for (auto mg : allMotorGroups)
    {
      mg->ResetEncoders();
    }
  }
}