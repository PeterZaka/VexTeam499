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
#include "inertial.h"
#include "auto.h"
#include "autoruns.h"
#include "drivehelp.h"
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

motor* team499::LeftWheelMotor = &driveLeft;
motor* team499::RightWheelMotor = &driveRight;

PID team499::LeftPID = PID(0.45,0,0);
PID team499::RightPID = PID(0.45,0,0);
PID team499::LeftTurnPID = PID(0.8, 0.1,0.2);
PID team499::RightTurnPID = PID(0.8,0.1,0.2);

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  calibrateInertial();
}


void autonomous(void)
{
  waitUntil(isCalibrated || canceledCalibration);
  if(canceledCalibration)
  {
    return;
  }

  vex::thread inertialThread(updateInertialForever);

  autoSkills();

  inertialThread.interrupt();
}

void usercontrol(void)
{
  waitUntil(isCalibrated || canceledCalibration);
  while (1)
  {
    updateGearShift();

    resetScreen();
    //printOnController("Power", gearShiftPower);
    // REMOVE THIS AFTER TESTING
    updateInertial();
    printOnController("X", xPos);
    printOnController("Y", yPos);
    printOnController("Rotation", rot);
    // REMOVE THIS AFTER TESTING

    axis3.Update();
    axis2.Update();
    l1.Update();
    l2.Update();
    r2.Update();
    x.Update();

    UpdateAllMotors();

    // using inertial sensor
    driveStraight(&LeftWheel, &RightWheel);
    turnToButton();

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