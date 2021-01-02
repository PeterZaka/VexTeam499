/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\MHS Robotics 1                                   */
/*    Created:      Tue Sep 08 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "motorGroup.h"
#include "toggleMotor.h"
#include "controllerInput.h"
#include "input.h"
#include <vector>

competition Competition;

using namespace vex;

std::vector<motorGroup*> motorGroup::s_allMotorGroups;

motorGroup LeftWheel("LeftWheel",[](){return round(Controller1.Axis3.position());},{&driveLeft});
motorGroup RightWheel("RightWheel",[](){return round(Controller1.Axis2.position() * 0.9);},{&driveRight});
motorGroup Intakes("Intakes",127,{&intakeLeft,&intakeRight});
toggleMotor FlyWheel("FlyWheel",&GetGearShiftPower,{&flywheelLeft,&flywheelRight});
motorGroup SideRollers("SideRollers",127,{&sideRollerLeft,&sideRollerRight});

controllerInput axis3([](){return abs(Controller1.Axis3.position()) > 10;},{&LeftWheel});
controllerInput axis2([](){return abs(Controller1.Axis2.position()) > 10;},{&RightWheel});
controllerInput l1([](){return Controller1.ButtonL1.pressing();},{},{&Intakes,&SideRollers});
controllerInput l2([](){return Controller1.ButtonL2.pressing();},{&Intakes,&SideRollers});
controllerInput r2([](){return Controller1.ButtonR2.pressing();},{&FlyWheel});

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


void autonomous(void)
{
  LeftWheel.SpinMotorsFor(100, 3250);
  RightWheel.SpinMotorsFor(100,3250);
  motorGroup::WaitUntilMotorGroupReaches(&LeftWheel, 3250);
  motorGroup::WaitUntilMotorGroupReaches(&RightWheel, 3250);
  LeftWheel.CorrectMotors(3250);
  RightWheel.CorrectMotors(3250);
  wait(500,msec);

  RightWheel.SpinMotorsFor(100,920);
  motorGroup::WaitUntilMotorGroupReaches(&RightWheel, 900);
  RightWheel.CorrectMotors(900);
  wait(500,msec);

  RightWheel.SpinMotorsFor(100,-920);
  motorGroup::WaitUntilMotorGroupReaches(&RightWheel, -900);
  RightWheel.CorrectMotors(-900);
  wait(500,msec);

  LeftWheel.SpinMotorsFor(100, -3250);
  RightWheel.SpinMotorsFor(100,-3250);
  motorGroup::WaitUntilMotorGroupReaches(&LeftWheel, -3250);
  motorGroup::WaitUntilMotorGroupReaches(&RightWheel, -3250);
  LeftWheel.CorrectMotors(-3250);
  RightWheel.CorrectMotors(-3250);
/*
  Intakes.spinMotorsFor(100,1000);
  motorGroup::WaitUntilMotorGroupReaches(&Intakes, 1000);
  FlyWheel.spinMotorsFor(30,3000);
  Intakes.spinMotorsFor(20, 300);
  motorGroup::WaitUntilMotorGroupReaches(&FlyWheel, 3000);
  Intakes.spinMotorsFor(50,-1000);
  Controller1.Screen.clearScreen();
  printThis(Intakes.averageRotation());
*/
}

void usercontrol(void)
{
  while(1)
  {
    updateGearShift();
    printGearShift();

    axis3.updateButton();
    axis2.updateButton();
    l1.updateButton();
    l2.updateButton();
    r2.updateButton();
    motorGroup::UpdateAllMotors();
    motorGroup::PrintWantedMotors();
    wait(20, msec);
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

/*
int main()
{
  vexcodeInit();
  while(1)
  {
    updateGearShift();
    printGearShift();

    axis3.updateButton();
    axis2.updateButton();
    l1.updateButton();
    l2.updateButton();
    r2.updateButton();
    motorGroup::updateAllMotors();
    wait(20, msec);
  }
}
*/