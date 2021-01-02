#include "motorGroup.h"

// CONSTRUCTORS

motorGroup::motorGroup(std::string name, double defaultPower,std::vector<vex::motor*> const& motors) :
m_name(name), m_defaultPower(defaultPower), m_powerFunction(nullptr), m_motors(motors)
{
  s_allMotorGroups.push_back(this);
}

motorGroup::motorGroup(std::string name, double (*powerFunction)(),std::vector<vex::motor*> const& motors) :
m_name(name), m_defaultPower(0), m_powerFunction(powerFunction), m_motors(motors)
{
  s_allMotorGroups.push_back(this);
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

void motorGroup::SpinMotorsFor(double pow, double degrees)
{
  ResetEncoders();
  for (auto m : m_motors)
  {
    m->startRotateFor(fwd, degrees, deg, pow, velocityUnits::pct);
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
  if (fabs(m_motors[0]->velocity(pct)) < 15 && fabs(this->AverageRotation()) > 10)
  {
    printf("%s: %.2lf\n", m_name.c_str(), AverageRotation());
    this->ResetEncoders();
  }
}


// STATIC FUNCTIONS

void motorGroup::WaitUntilMotorGroupReaches(motorGroup* group, float degrees)
{
  while (fabs(group->AverageRotation()) < fabs(degrees * 0.95))
  {
    wait(100, msec);
  }
}

void motorGroup::UpdateAllMotors()
{
  for(auto mg: s_allMotorGroups)
  {
    mg->UpdateDefaultPower();
    mg->Update();
  }
}

void motorGroup::PrintWantedMotors()
{
  for(auto mg: s_allMotorGroups)
  {
    mg->PrintRotation();
  }
}

void motorGroup::ResetAllMotorRotations()
{
  for(auto mg: s_allMotorGroups)
  {
    mg->ResetEncoders();
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

void motorGroup::UpdateDefaultPower()
{
  if (m_powerFunction != nullptr)
  {
    m_currentPower = m_powerFunction();
  }
}
