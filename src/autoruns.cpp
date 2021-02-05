#include "autoruns.h"

#define add(x) tasks.push_back([](){x;})

bool isReady = false;

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
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(150));
  add(SideRollers.SpinMotorsAt(100));
  add(wait(1.5,sec));
  add(SideRollers.Stop());
  // move ball 0 and ball 1 to top
  add(Intakes.SpinMotorsTo(100, 1200));
  add(Intakes.WaitUntilReaches(1200));
  // move ball 0 and ball 1 back and get flywheel ready
  add(Intakes.SpinMotorsTo(-100, -400));
  add(Intakes.WaitUntilReaches(-400));
  add(FlyWheel.SpinMotorsAt(30));
  add(wait(0.5, sec));
  add(ready());

  // drive close to bottom left tower and go over ball 1
  driveForward(1550, degrees);

  // turn to bottom left tower
  turnTo(-145);

  // drive to bottom left tower
  SideRollers.SpinMotorsAt(100);
  driveForward(700, degrees);

  // score ball 0 at bottom left tower
  shoot();
  turnTo(-145);

  // ---------- BOTTOM LEFT TOWER SCORED ----------

  /*
      - Descore all of middle tower
      - Score ball 1 at middle tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));
  // move ball 1 to top
  add(Intakes.WaitUntilReaches(-600));
  add(Intakes.SpinMotorsTo(100, 1400));
  add(Intakes.WaitUntilReaches(1400));
  add(Intakes.SpinMotorsTo(-100, -400));
  add(Intakes.WaitUntilReaches(-400));

  // drive to y-middle
  driveForward(-2100, degrees);
  maxPower = 30;
  driveForward(-435, degrees);
  maxPower = 100;

  // turn to middle tower
  turnTo(90);

  // descore 3 times in middle tower
  driveForward(1000, degrees);
  turnTo(90);
  driveForward(-350, degrees);

  closeEnoughRot = 0.7;
  turnTo(90);
  resetCloseEnoughs();
  
  driveForward(500, degrees);
  turnTo(90);
  driveForward(-350, degrees);

  closeEnoughRot = 0.7;
  turnTo(90);
  resetCloseEnoughs();

  // descore and prepare to score
  add(FlyWheel.SpinMotorsAt(30));
  add(ready());
  driveForward(500, degrees);
  driveForward(-70, degrees);

  // turn to middle goal
  turnTo(48);
  shoot();

  // "reset" robot
  turnTo(90);
  driveForward(500, degrees);
  turnTo(90);

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
  Intakes.SpinMotorsTo(100, 400);

  // point to ball 3 / top right tower
  turnTo(58);

  // move ball 2 and ball 3 to top
  add(LeftWheel.WaitUntilReaches(1600));
  add(Intakes.SpinMotorsTo(100, 1000));
  add(Intakes.WaitUntilReaches(1000));
  add(Intakes.SpinMotorsTo(-100, -200));
  add(Intakes.WaitUntilReaches(-200));
  add(FlyWheel.SpinMotorsAt(30));
  add(wait(0.5, sec));
  add(ready());

  // drive to top right tower
  driveForward(3200, degrees);

  // score ball 2 at top right tower
  shoot();

  // ---------- TOP RIGHT TOWER SCORED ----------

  /*
      - Collect ball 4
      - Score ball 3 at middle right tower
  */

  // back up to x-axis of ball 4
  driveForward(-500, degrees);

  // get rid of blue ball
  Intakes.SpinMotorsTo(-100, -600);
  SideRollers.SpinMotorsTo(-70, -2000);

  // turn to ball 4
  turnTo(180);
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // move ball 3 to bottom
  add(Intakes.SpinMotorsTo(-100, -800));

  // drive to ball 4 / x-axis of middle right tower
  driveForward(2400, degrees);
  
  // move ball 3 and ball 4 to top
  Intakes.SpinMotorsTo(100, 1500);
  add(Intakes.WaitUntilReaches(1500));
  add(Intakes.SpinMotorsTo(-100, -400));
  add(Intakes.WaitUntilReaches(-400));
  add(FlyWheel.SpinMotorsAt(30));
  add(wait(0.5, sec));
  add(ready());

  // turn to middle right tower
  turnTo(90);

  // drive to middle right tower
  driveForward(600, degrees);

  // score ball 3 at middle right tower
  shoot();

  // ---------- MIDDLE RIGHT TOWER SCORED ----------

  /*
      - Score ball 4 at bottom right tower
  */

  // back up from middle right tower
  driveForward(-300, degrees);

  // get rid of blue ball
  Intakes.SpinMotorsTo(-100, -600);
  SideRollers.SpinMotorsTo(-70, -2000);

  // move ball 4 to top
  add(Intakes.WaitUntilReaches(-600));
  add(Intakes.SpinMotorsTo(100, 1000));
  add(Intakes.WaitUntilReaches(1000));
  add(Intakes.SpinMotorsTo(-100, -400));
  add(Intakes.WaitUntilReaches(-400));

  // point close to bottom right tower
  turnTo(180);

  // move close to bottom right tower
  driveForward(2200, degrees);

  // point to bottom right tower
  turnTo(135);

  // drive to bottom right tower
  add(FlyWheel.SpinMotorsAt(30));
  add(ready());
  SideRollers.SpinMotorsAt(100);
  driveForward(900, degrees);

  // score ball 4 at bottom right tower
  shoot();

  // ---------- BOTTOM RIGHT TOWER SCORED ----------

  /*
      - Collect ball 5
      - Score ball 5 at bottom middle tower
  */

  // back up from bottom right tower
  driveForward(-1000, degrees);

  // get rid of blue ball
  Intakes.SpinMotorsTo(-100, -600);
  SideRollers.SpinMotorsTo(-70, -2000);

  // turn to ball 5
  turnTo(300);

  // drive to ball 5 / y-axis of bottom middle tower
  SideRollers.SpinMotorsAt(100);
  driveForward(2500, degrees);

  // move ball 5 to top
  Intakes.SpinMotorsTo(100, 1400);
  add(Intakes.WaitUntilReaches(1400));
  add(Intakes.SpinMotorsTo(-100, -400));
  add(Intakes.WaitUntilReaches(-400));

  // turn to bottom middle tower
  turnTo(180);

  // drive to bottom middle tower
  add(FlyWheel.SpinMotorsAt(30));
  add(ready());
  driveForward(2250, degrees);

  // score ball 5 at bottom middle tower
  shoot();

  // drive out / get rid of everything
  driveForward(-1000, degrees);
  Intakes.SpinMotorsTo(-60, -1200);
  SideRollers.SpinMotorsTo(-50, -4000);

  taskThread.interrupt();

}

void shoot()
{
  waitUntil(isReady);
  Intakes.SpinMotorsTo(100, 500);
  Intakes.WaitUntilReaches(500);
  FlyWheel.Stop();
  isReady = false;
}

void ready()
{
  isReady = true;
}