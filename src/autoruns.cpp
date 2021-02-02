#include "autoruns.h"

#define add(x) tasks.push_back([](){x;})

/*

O        O        O
    *         3
*        2        *

O *   *  O  *   4 O
  
*        5        *
    1         *
O      # O        O

*/

void autoSkills()
{
  using namespace team499;
  using team499::degrees;

  vex::thread taskThread(runTasks);

  /*
      - Set up robot
      - Collect ball 1
      - Score at ball 0 bottom left tower
  */
  
  // Set up robot and put ball 0 near bottom
  add(Intakes.SpinMotorsTo(30,400));
  add(SideRollers.SpinMotorsAt(100));
  add(Intakes.WaitUntilReaches(400));

  add(SideRollers.Stop());

  // drive to y-axis ball 1
  driveForward(500, degrees);

  // point towards ball 1
  turnTo(-90);

  // pick up ball 1
  add(LeftWheel.WaitUntilReaches(150));
  add(SideRollers.SpinMotorsAt(100));
  // move ball 0 and ball 1 to top
  add(wait(1.5,sec));
  add(Intakes.SpinMotorsTo(100, 1200));
  add(SideRollers.Stop());
  add(Intakes.WaitUntilReaches(1200));
  // move ball 0 and ball 1 back and get flywheel ready
  add(Intakes.SpinMotorsTo(-100, -400));
  add(Intakes.WaitUntilReaches(-400));
  add(FlyWheel.SpinMotorsAt(30));

  // drive close to bottom left tower and go over ball 1
  driveForward(1550, degrees);

  // turn to bottom left tower
  turnTo(-145);

  // drive to bottom left tower
  SideRollers.SpinMotorsAt(100);
  driveForward(625, degrees);

  // score ball 0 at bottom left tower
  Intakes.WaitUntilReaches(-400);
  Intakes.SpinMotorsTo(60, 500);
  Intakes.WaitUntilReaches(500);
  FlyWheel.Stop();

  // ---------- BOTTOM LEFT TOWER SCORED ----------

  /*
      - Descore all of middle tower
      - Score ball 1 at middle tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-60, -600));
  add(SideRollers.SpinMotorsTo(-50, -2000));

  // drive to y-middle
  driveForward(-2550, degrees);

  // turn to middle tower
  turnTo(90);

  // move ball 1 to top
  add(Intakes.SpinMotorsTo(100, 1400));
  add(Intakes.WaitUntilReaches(1400));
  add(Intakes.SpinMotorsTo(-100, -400));

  // descore 3 times in middle tower
  driveForward(700, degrees);
  driveForward(-300, degrees);

  driveForward(325, degrees);
  turnTo(90);
  driveForward(-300, degrees);

  // descore and prepare to score
  FlyWheel.SpinMotorsAt(30);
  driveForward(325, degrees);

  // allow robot to not reach target
  closeEnoughDeg = 10000;
  closeEnoughRot = 360;
  targetTime = 200;
  // turn to middle goal
  turnTo(48);
  Intakes.SpinMotorsTo(60, 400);
  Intakes.WaitUntilReaches(400);
  FlyWheel.Stop();

  // "reset" robot
  turnTo(90);
  driveForward(500, degrees);
  turnTo(90);
  resetCloseEnoughs();

  // back out of middle goal
  driveForward(-700, degrees);

  // ---------- MIDDLE TOWER DESCORED/SCORED ----------

  /*
      - Collect ball 2
      - Collect ball 3
      - Score ball 2 at top right tower
  */

  // turn to ball 2
  turnTo(39);

  // drive to ball 2
  SideRollers.SpinMotorsAt(100);
  driveForward(1700, degrees);
  
  // make room for ball 3
  Intakes.SpinMotorsTo(60, 400);

  // point to ball 3 / top right tower
  turnTo(55);

  // move ball 2 and ball 3 to top
  add(LeftWheel.WaitUntilReaches(1600));
  add(Intakes.SpinMotorsTo(80, 1000));
  add(Intakes.WaitUntilReaches(1000));
  add(Intakes.SpinMotorsTo(-80, -400));
  add(Intakes.WaitUntilReaches(-400));
  add(FlyWheel.SpinMotorsAt(30));
  add(wait(1, sec));

  // drive to top right tower
  driveForward(2950, degrees);

  // score ball 2 at top right tower
  add(Intakes.SpinMotorsTo(60, 600));
  Intakes.WaitUntilReaches(600);
  FlyWheel.Stop();

  // ---------- TOP RIGHT TOWER SCORED ----------

  /*
      - Collect ball 4
      - Score ball 3 at middle right tower
  */

  // back up to x-axis of ball 4
  driveForward(-500, degrees);

  // get rid of blue ball
  Intakes.SpinMotorsTo(-60, -600);
  SideRollers.SpinMotorsTo(-50, -2000);

  // turn to ball 4
  turnTo(180);
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // move ball 3 to bottom
  add(Intakes.SpinMotorsTo(-60, -800));

  // drive to ball 4 / x-axis of middle right tower
  driveForward(2400, degrees);
  
  // move ball 3 and ball 4 to top
  Intakes.SpinMotorsTo(60, 1500);
  add(Intakes.WaitUntilReaches(1500));
  add(Intakes.SpinMotorsTo(-60, -400));
  add(Intakes.WaitUntilReaches(-400));
  add(FlyWheel.SpinMotorsAt(30));

  // turn to middle right tower
  turnTo(90);

  // drive to middle right tower
  driveForward(600, degrees);

  // score ball 3 at middle right tower
  Intakes.SpinMotorsTo(60, 400);
  Intakes.WaitUntilReaches(400);
  FlyWheel.Stop();

  // ---------- MIDDLE RIGHT TOWER SCORED ----------

  /*
      - Score ball 4 at bottom right tower
  */

  // back up from middle right tower
  driveForward(-300, degrees);

  // get rid of blue ball
  Intakes.SpinMotorsTo(-60, -600);
  SideRollers.SpinMotorsTo(-50, -2000);

  // move ball 4 to top
  add(Intakes.WaitUntilReaches(-600));
  add(Intakes.SpinMotorsTo(60, 1000));
  add(Intakes.WaitUntilReaches(1000));
  add(Intakes.SpinMotorsTo(-60, -400));

  // point close to bottom right tower
  turnTo(180);

  // move close to bottom right tower
  driveForward(2000, degrees);

  // point to bottom right tower
  turnTo(135);

  // drive to bottom right tower
  FlyWheel.SpinMotorsAt(30);
  SideRollers.SpinMotorsAt(100);
  driveForward(900, degrees);

  // score ball 4 at bottom right tower
  Intakes.SpinMotorsTo(60, 500);
  Intakes.WaitUntilReaches(500);
  FlyWheel.Stop();

  // ---------- BOTTOM RIGHT TOWER SCORED ----------

  /*
      - Collect ball 5
      - Score ball 5 at bottom middle tower
  */

  // back up from bottom right tower
  driveForward(-1000, degrees);

  // get rid of blue ball
  Intakes.SpinMotorsTo(-60, -600);
  SideRollers.SpinMotorsTo(-50, -2000);

  // turn to ball 5
  turnTo(315);

  // drive to ball 5 / y-axis of bottom middle tower
  SideRollers.SpinMotorsAt(100);
  driveForward(500, degrees);

  // move ball 5 to top
  Intakes.SpinMotorsTo(60, 1400);
  add(Intakes.WaitUntilReaches(1400));
  add(Intakes.SpinMotorsTo(-60, -400));

  // turn to bottom middle tower
  turnTo(180);

  // drive to bottom middle tower
  FlyWheel.SpinMotorsAt(30);
  driveForward(1250, degrees);

  // score ball 5 at bottom middle tower
  Intakes.SpinMotorsTo(60, 500);
  Intakes.WaitUntilReaches(500);
  FlyWheel.Stop();

  // drive out / get rid of everything
  driveForward(-1000, degrees);
  Intakes.SpinMotorsTo(-60, -1200);
  SideRollers.SpinMotorsTo(-50, -4000);

  taskThread.interrupt();

}