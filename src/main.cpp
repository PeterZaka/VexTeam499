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
#include "motors.h"
#include <vector>

competition Competition;

using namespace vex;
using namespace team499;

std::vector<motorGroup*> team499::allMotorGroups;

input axis3([]() {return abs(Controller1.Axis3.position()) > 10; }, { &LeftWheel });
input axis2([]() {return abs(Controller1.Axis2.position()) > 10; }, { &RightWheel });

input l1([]() {return Controller2.ButtonL1.pressing(); }, {}, { &Intakes,&SideRollers }); // move down and descore
input l2([]() {return Controller2.ButtonL2.pressing(); }, { &Intakes,&SideRollers }); // move up and intake
input r2([]() {return Controller2.ButtonR2.pressing(); }, { &FlyWheel }); // turn on/off flywheel
input x([]() {return Controller2.ButtonX.pressing(); }, { &Intakes }, { &SideRollers }); // move up and descore
input a([]() {return Controller2.ButtonA.pressing(); }, { &Intakes } ); // only move up

motor* team499::LeftWheelMotor = &driveLeft;
motor* team499::RightWheelMotor = &driveRight;

PID team499::DrivePID = PID(0.29, 0, 0);
PID team499::TurnPID = PID(1.1, 0, 0.1);

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
  canceledCalibration = true; // do not callibrate in usercontrol

  waitUntil(isCalibrated || canceledCalibration);
  if(isCalibrated && !canceledCalibration)
  {
    vex::thread inertailThread(updateInertialForever);
  }

  while (1)
  {
    Controller2.Screen.clearScreen();

    updateGearShift();

    axis3.Update();
    axis2.Update();
    l1.Update();
    l2.Update();
    r2.Update();
    x.Update();
    a.Update();

    if(detects(SIG_RED))
    {
      Intakes.m_currentPower = std::min(0.0, Intakes.m_currentPower);
    }
    if(Controller2.ButtonY.pressing())
    {
      Intakes.SpinMotorsTo(100, 500);
    }

    UpdateAllMotors();

    // using inertial sensor
    driveStraight(&LeftWheel, &RightWheel);
    //turnToButton();

    Controller2.Screen.print("Power: %.2lf", gearShiftPower);

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