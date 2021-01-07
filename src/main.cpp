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
#include "input.h"
#include "common.h"
#include <vector>

competition Competition;

using namespace vex;
using namespace team499;

std::vector<motorGroup*> team499::allMotorGroups;

motorGroup LeftWheel("LeftWheel", []() {return round(Controller1.Axis3.position()); }, { &driveLeft });
motorGroup RightWheel("RightWheel", []() {return round(Controller1.Axis2.position() * 0.9); }, { &driveRight });
motorGroup Intakes("Intakes", 127, { &intakeLeft,&intakeRight });
toggleMotor FlyWheel("FlyWheel", &GetGearShiftPower, { &flywheelLeft,&flywheelRight });
motorGroup SideRollers("SideRollers", 127, { &sideRollerLeft,&sideRollerRight });

input axis3([]() {return abs(Controller1.Axis3.position()) > 10; }, { &LeftWheel });
input axis2([]() {return abs(Controller1.Axis2.position()) > 10; }, { &RightWheel });
input l1([]() {return Controller2.ButtonL1.pressing(); }, {}, { &Intakes,&SideRollers });
input l2([]() {return Controller2.ButtonL2.pressing(); }, { &Intakes,&SideRollers });
input r2([]() {return Controller2.ButtonR2.pressing(); }, { &FlyWheel });
input x([]() {return Controller2.ButtonX.pressing(); }, { &Intakes }, { &SideRollers });

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


void autonomous(void)
{

  //Part 1
  Intakes.SpinMotorsAt(30);
  SideRollers.SpinMotorsAt(100);
  wait(3, sec);
  Intakes.SpinMotorsAt(0);
  SideRollers.SpinMotorsAt(0);

  // forward
  Intakes.SpinMotorsAt(-60);
  LeftWheel.SpinMotorsTo(50, 700);
  RightWheel.SpinMotorsTo(50, 700);
  LeftWheel.WaitUntilReaches(700);
  RightWheel.WaitUntilReaches(700);
  Intakes.SpinMotorsAt(0);

  // turn left
  LeftWheel.SpinMotorsTo(-50, -470);
  RightWheel.SpinMotorsTo(50, 470);
  LeftWheel.WaitUntilReaches(-470);
  RightWheel.WaitUntilReaches(470);

  // drive forward
  SideRollers.SpinMotorsAt(100);
  Intakes.SpinMotorsAt(70);
  LeftWheel.SpinMotorsTo(50, 1675);
  RightWheel.SpinMotorsTo(50, 1675);
  LeftWheel.WaitUntilReaches(1675);
  RightWheel.WaitUntilReaches(1675);
  SideRollers.SpinMotorsAt(0);
  Intakes.SpinMotorsAt(0);

  // turn left
  Intakes.SpinMotorsAt(-65);
  LeftWheel.SpinMotorsTo(-50, -225);
  RightWheel.SpinMotorsTo(50, 225);
  LeftWheel.WaitUntilReaches(-225);
  RightWheel.WaitUntilReaches(225);
  Intakes.SpinMotorsAt(0);

  // drive forward
  LeftWheel.SpinMotorsAt(50);
  RightWheel.SpinMotorsAt(50);
  wait(1, sec);
  LeftWheel.SpinMotorsAt(0);
  RightWheel.SpinMotorsAt(0);

  //Score ball at first tower
  FlyWheel.SpinMotorsTo(50, 1500);
  wait(.40, sec);
  SideRollers.SpinMotorsAt(100);
  Intakes.SpinMotorsAt(100);
  FlyWheel.WaitUntilReaches(1500);
  Intakes.SpinMotorsAt(100);
  SideRollers.SpinMotorsAt(100);

  wait(1, sec);

  Intakes.SpinMotorsAt(0);
  SideRollers.SpinMotorsAt(0);

  //Part 2

  // drive backward
  Intakes.SpinMotorsAt(-50);
  SideRollers.SpinMotorsAt(-50);
  LeftWheel.SpinMotorsTo(-50, -2650);
  RightWheel.SpinMotorsTo(-50, -2650);
  Intakes.SpinMotorsAt(0);
  SideRollers.SpinMotorsAt(0);
  LeftWheel.WaitUntilReaches(2650);
  RightWheel.WaitUntilReaches(2650);

  //Turn Left
  LeftWheel.SpinMotorsTo(-50, -626);
  RightWheel.SpinMotorsTo(50, 626);
  LeftWheel.WaitUntilReaches(-626);
  RightWheel.WaitUntilReaches(626);

  //Drive Forward
  SideRollers.SpinMotorsAt(150);
  LeftWheel.SpinMotorsAt(50);
  RightWheel.SpinMotorsAt(50);
  wait(1.5, sec);

  //Drive Backward
  LeftWheel.SpinMotorsTo(-50, -450);
  RightWheel.SpinMotorsTo(-50, -500);
  LeftWheel.WaitUntilReaches(-450);
  RightWheel.WaitUntilReaches(-500);

  //Drive Forward
  LeftWheel.SpinMotorsAt(50);
  RightWheel.SpinMotorsAt(50);
  wait(1.5, sec);

  //Drive Backward
  LeftWheel.SpinMotorsTo(-50, -450);
  RightWheel.SpinMotorsTo(-50, -500);
  LeftWheel.WaitUntilReaches(-450);
  RightWheel.WaitUntilReaches(-500);

  //Drive Forward
  LeftWheel.SpinMotorsAt(50);
  RightWheel.SpinMotorsAt(50);
  wait(1.5, sec);

  //Drive Backward
  LeftWheel.SpinMotorsTo(-50, -450);
  RightWheel.SpinMotorsTo(-50, -500);
  LeftWheel.WaitUntilReaches(-450);
  RightWheel.WaitUntilReaches(-500);

  //Drive Forward
  LeftWheel.SpinMotorsAt(50);
  RightWheel.SpinMotorsAt(50);
  wait(1, sec);

  //Part 3A

  //Drive Backward
  LeftWheel.SpinMotorsTo(50, -900);
  RightWheel.SpinMotorsTo(50, -900);
  SideRollers.SpinMotorsTo(50, -50);
  LeftWheel.WaitUntilReaches(-900);
  RightWheel.WaitUntilReaches(-900);
  SideRollers.WaitUntilReaches(-50);

  //Turn Left
  LeftWheel.SpinMotorsTo(50, -290);
  RightWheel.SpinMotorsTo(50, 290);
  LeftWheel.WaitUntilReaches(-290);
  RightWheel.WaitUntilReaches(290);

  // turn right a little
  LeftWheel.SpinMotorsAt(70);
  RightWheel.SpinMotorsAt(48);
  wait(2, sec);

  //Drive Forward a Little
  LeftWheel.SpinMotorsTo(50, 450);
  RightWheel.SpinMotorsTo(50, 450);
  LeftWheel.WaitUntilReaches(450);
  RightWheel.WaitUntilReaches(450);

  //Turn Left
  LeftWheel.SpinMotorsTo(-50, -260);
  RightWheel.SpinMotorsTo(50, 260);
  LeftWheel.WaitUntilReaches(-260);
  RightWheel.WaitUntilReaches(260);

  //Drive Forward into wall
  SideRollers.SpinMotorsAt(80);
  LeftWheel.SpinMotorsTo(75, 3300);
  RightWheel.SpinMotorsTo(73, 3300);
  wait(6, sec);
  SideRollers.SpinMotorsAt(0);

  //Score Ball
  wait(1.5, sec);
  FlyWheel.SpinMotorsTo(50, 2500);
  wait(1, sec);
  SideRollers.SpinMotorsAt(1600);
  Intakes.SpinMotorsAt(1600);
  FlyWheel.WaitUntilReaches(2500);
  Intakes.SpinMotorsAt(0);
  SideRollers.SpinMotorsAt(0);

  //Descore Goal
  SideRollers.SpinMotorsAt(1000);
  Intakes.SpinMotorsAt(1000);
  wait(3, sec);
  Intakes.SpinMotorsAt(0);
  SideRollers.SpinMotorsAt(0);

  // final backout
  LeftWheel.SpinMotorsTo(-50, -200);
  RightWheel.SpinMotorsTo(-50, -200);

}

void usercontrol(void)
{
  while (1)
  {
    updateGearShift();
    printGearShift();

    axis3.Update();
    axis2.Update();
    l1.Update();
    l2.Update();
    r2.Update();
    x.Update();

    UpdateAllMotors();

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