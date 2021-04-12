#pragma once

/*

- Use smart pointers from <memory>
- Semi-useless class because vex has a motor_group class - read API first

*/

#include <vector>
#include "vex.h"
#include "common.h"

namespace team499 {

  class motorGroup
  {

    friend class input;

  public:

    // CONSTRUCTORS

    // motorGroup groups together motors to allow easier control
    // defaultPower - power of the motorGroup that changes from 0 to a number that doesn't change
    // powerFunction - power of the motorGroup that changes from 0 to a number that does change
    motorGroup(std::string name, double defaultPower, const std::vector<vex::motor*>& motors);
    motorGroup(std::string name, double (*powerFunction)(), const std::vector<vex::motor*>& motors);

    // HELPER FUNCTIONS
    float AverageRotation() const;
    void ResetEncoders();

    // AUTONOMOUS FUNCTIONS
    void SpinMotorsTo(double pow, double degrees);
    void Stop();
    void CorrectMotors(double degrees);
    void WaitUntilReaches(float degrees);

    // USERCONTROL FUNCTIONS
    void SpinMotorsAt(double const motorGroupPower) const;

    // MISC
    void PrintRotation();

    // checks if has a power function and applies it
    void UpdateDefaultPower();

    // Updates motor (Use UpdateAllMotors at end of cycle instead)
    virtual void Update()
    {
      SpinMotorsAt(m_currentPower * m_anyButtonPressed);
      m_anyButtonPressed = false;
    }

    double m_currentPower;

  protected:

    // true if button pressed during cycle
    bool m_anyButtonPressed;


  private:

    // called when in positive group and button pressed
    void PositiveActivate();

    // called when in negative group and button pressed
    void NegativeActivate();


    // name of motor group
    std::string m_name;

    // determines power with constant value
    const double m_defaultPower;

    // determines power with changing value
    double (*m_powerFunction)();

    // motors in the motor group
    std::vector<vex::motor*> m_motors;
  };

  // Usercontrol - Calls update for all motor groups
  void UpdateAllMotors();

  // Usercontrol (optional) - Used to record usercontrol
  void PrintWantedMotors();

  // Misc - Reset all motor rotations from all groups
  void ResetAllMotorRotations();

  extern std::vector<motorGroup*> allMotorGroups;

}