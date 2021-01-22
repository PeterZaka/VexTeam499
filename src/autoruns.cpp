#include "autoruns.h"

#define add(x) tasks.push_back([](){x;})

void autoSkills()
{
  using namespace team499;
  using team499::degrees;

  vex::thread taskThread(runTasks);

  // Set up robot
  add(Intakes.SpinMotorsAt(30));
  add(SideRollers.SpinMotorsAt(100));
  add(Intakes.WaitUntilReaches(600));
  add(Intakes.SpinMotorsTo(-60,600));

  // forward
  driveForward(600, degrees);

  // turn left
  turnTo(-90);

  // drive forward
  SideRollers.SpinMotorsAt(100);
  Intakes.SpinMotorsAt(30);
  driveForward(1500, degrees);
  SideRollers.SpinMotorsAt(0);
  Intakes.SpinMotorsAt(0);

  // turn left
  turnTo(-145);

  // drive forward
  SideRollers.SpinMotorsAt(100);
  driveForward(650, degrees);

  //Score ball at first tower
  FlyWheel.SpinMotorsTo(30, 1500);
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
  SideRollers.SpinMotorsAt(-50);
  Intakes.SpinMotorsAt(-50);

  driveForward(-2550, degrees);

  Intakes.SpinMotorsAt(0);
  SideRollers.SpinMotorsAt(0);

  //Turn to 90
  turnTo(90);

  //Drive Forward
  SideRollers.SpinMotorsAt(60);

  driveForward(625, degrees);
  turnTo(90);
  driveForward(-300, degrees);

  driveForward(300, degrees);
  turnTo(90);
  driveForward(-300, degrees);

  driveForward(300, degrees);
  turnTo(90);
  driveForward(-700, degrees);

  // point towards red ball
  turnTo(45);

  // get ball
  SideRollers.SpinMotorsAt(50);
  driveForward(1700, degrees);

  turnTo(55);

  driveForward(2900, degrees);

  FlyWheel.SpinMotorsTo(30, 1500);
  SideRollers.SpinMotorsAt(100);
  Intakes.SpinMotorsAt(100);
  FlyWheel.WaitUntilReaches(1500);
  Intakes.SpinMotorsAt(100);
  SideRollers.SpinMotorsAt(100);

  taskThread.interrupt();

}