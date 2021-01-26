#include "autoruns.h"

#define add(x) tasks.push_back([](){x;})

/*

O        O        O
    *         3
*        2        *

O *   *  O  *   4 O
  
*        *        *
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

  //add(Intakes.SpinMotorsTo(-60, -350));
  add(SideRollers.Stop());

  // drive to y-axis ball 1
  driveForward(500, degrees);

  // point towards ball 1
  turnTo(-90);

  // pick up ball 1
  add(LeftWheel.WaitUntilReaches(300));
  add(SideRollers.SpinMotorsAt(100));
  // move both ball 0 and ball 1 to top
  add(wait(2,sec));
  add(Intakes.SpinMotorsTo(60, 1200));
  add(SideRollers.Stop());
  add(Intakes.WaitUntilReaches(1200));
  add(Intakes.SpinMotorsTo(-60, -400));

  // drive close to bottom left tower and go over ball 1
  driveForward(1550, degrees);

  // turn to bottom left tower
  turnTo(-145);

  // drive to bottom left tower
  Intakes.WaitUntilReaches(-400);
  FlyWheel.SpinMotorsAt(30);
  SideRollers.SpinMotorsAt(100);
  driveForward(625, degrees);

  // score ball 0 at bottom left tower
  Intakes.SpinMotorsTo(60, 500);
  Intakes.WaitUntilReaches(500);
  FlyWheel.Stop();

  // ---------- BOTTOM LEFT TOWER SCORED ----------

  /*
      - Descore all of middle tower
      - Score ball 1 at middle tower
  */

  // drive to y-middle
  Intakes.SpinMotorsTo(-60, -600);
  SideRollers.SpinMotorsTo(-50, -2000);
  driveForward(-2550, degrees);

  // turn to middle tower
  turnTo(90);

  // move ball 1 to top
  add(Intakes.SpinMotorsTo(60, 1400));
  add(Intakes.WaitUntilReaches(1400));
  add(Intakes.SpinMotorsTo(-60, -400));

  // descore 3 times in middle tower
  driveForward(700, degrees);
  driveForward(-300, degrees);

  driveForward(325, degrees);
  driveForward(-300, degrees);

  // descore and score
  FlyWheel.SpinMotorsAt(30);
  driveForward(325, degrees);

  int a = closeEnoughDegreesRot;
  int b = targetTime;
  int c = closeEnoughDegrees;
  closeEnoughDegrees = 10000;
  closeEnoughDegreesRot = 360;
  targetTime = 200;

  turnTo(48);
  Intakes.SpinMotorsTo(60, 400);
  Intakes.WaitUntilReaches(400);
  FlyWheel.Stop();
  targetTime = 200;
  turnTo(90);
  driveForward(500, degrees);
  turnTo(90);

  closeEnoughDegreesRot = a;
  targetTime = b;
  closeEnoughDegrees = c;
  driveForward(-700, degrees);

  // ---------- MIDDLE TOWER DESCORED/SCORED ----------

  /*
      - Collect ball 2
      - Collect ball 3
      - Score ball 2 at top right tower
  */

  // turn to ball 2
  turnTo(40);

  // drive to ball 2
  SideRollers.SpinMotorsAt(100);
  driveForward(1700, degrees);
  
  // make room for ball 3
  Intakes.SpinMotorsTo(60, 400);

  // point to ball 3 / top right tower
  turnTo(53);

  // move ball 2 and ball 3 to top
  add(LeftWheel.WaitUntilReaches(1600));
  add(Intakes.SpinMotorsTo(70, 900));
  add(Intakes.WaitUntilReaches(900));
  add(Intakes.SpinMotorsTo(-80, -600));
  add(Intakes.WaitUntilReaches(-600));
  add(FlyWheel.SpinMotorsAt(30));

  // drive to top right tower
  driveForward(2950, degrees);

  // score ball 2 at top right tower
  wait(1, sec);
  Intakes.SpinMotorsTo(60, 1200);
  Intakes.WaitUntilReaches(1200);
  FlyWheel.Stop();

  // ---------- TOP RIGHT TOWER SCORED ----------

  /*
      - Collect ball 4
      - Score ball 3 at middle right tower
  */

  // back up to x-axis of ball 4
  driveForward(-1000, degrees);

  // turn to ball 4
  SideRollers.SpinMotorsAt(-100);
  turnTo(180);
  Intakes.SpinMotorsTo(-60, -1400);
  SideRollers.SpinMotorsAt(100);

  // drive to ball 4 / x-axis of middle right tower
  driveForward(2000, degrees);
  
  // move ball 3 and ball 4 to top
  Intakes.SpinMotorsTo(60, 1500);
  Intakes.SpinMotorsTo(-60, 1500);

  // turn to middle right tower
  turnTo(90);

  // drive to middle right tower
  FlyWheel.SpinMotorsAt(30);
  driveForward(800, degrees);

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

  // move ball 4 to top
  SideRollers.SpinMotorsTo(100, -1000);
  add(SideRollers.WaitUntilReaches(-1000));
  add(Intakes.SpinMotorsTo(60, 300));

  // point close to bottom right tower
  turnTo(180);

  // move close to bottom right tower
  driveForward(2000, degrees);

  // point to bottom right tower
  turnTo(135);

  // drive to bottom right tower
  SideRollers.SpinMotorsAt(-100);
  wait(.25, sec);
  FlyWheel.SpinMotorsAt(30);
  driveForward(900, degrees);

  // score ball 4 at bottom right tower
  Intakes.SpinMotorsTo(60, 600);
  Intakes.WaitUntilReaches(400);
  FlyWheel.Stop();

  // back up from bottom right tower
  driveForward(-1000, degrees);
  SideRollers.SpinMotorsTo(-100, -1000);

  taskThread.interrupt();

}