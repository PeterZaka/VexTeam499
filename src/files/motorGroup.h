#pragma once

#include <vector>
#include "string.h"
#include "input.h"
#include "vex.h"

class motorGroup
{

  friend class controllerInput;

public:

  // CONSTRUCTORS
  motorGroup(std::string name, double defaultPower, const std::vector<vex::motor*>& motors);
  motorGroup(std::string name, double (*powerFunction)(), const std::vector<vex::motor*>& motors);

  // HELPER FUNCTIONS
  float AverageRotation() const;
  void ResetEncoders();

  // AUTONOMOUS FUNCTIONS
  void SpinMotorsFor(double pow, double degrees);
  void CorrectMotors(double degrees);

  // USERCONTROL FUNCTIONS
  void SpinMotorsAt(double const motorGroupPower) const;

  // MISC
  void PrintRotation();


  // STATIC FUNCTIONS
  
  // Autonomous - Rework into non-static
  static void WaitUntilMotorGroupReaches(motorGroup* group, float degrees);

  // Usercontrol - Calls update for all motor groups
  static void UpdateAllMotors();

  // Usercontrol (optional) - Used to record usercontrol
  static void PrintWantedMotors();

  // Misc - Reset all motor rotations from all groups
  static void ResetAllMotorRotations();


protected:
  
  // Always called once per cycle at the end
  virtual void Update()
  {
    SpinMotorsAt(m_currentPower * m_anyButtonPressed);
    m_anyButtonPressed = false;
  }

  // true if button pressed during cycle
  bool m_anyButtonPressed;
  
  double m_currentPower;


private:

  // called when in positive group and button pressed
  void PositiveActivate();

  // called when in negative group and button pressed
  void NegativeActivate();

  // checks if has a power function and applies it
  void UpdateDefaultPower();


  // has all the motor groups
  static std::vector<motorGroup*> s_allMotorGroups;

  // name of motor group
  std::string m_name;

  // determines power with constant value
  const double m_defaultPower;

  // determines power with changing value
  double (*m_powerFunction)();

  // motors in the motor group
  std::vector<vex::motor*> m_motors;
};