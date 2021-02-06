#include "autoruns.h"

#define add(x) tasks.push_back([](){x;})

bool isReady = false;

/*

O        O        O
    3         5
*        4        *

O 2   *  O  *   6 O
  
*        *        *
    1         7
O        O #      O

*/

void autoSkills()
{
  using namespace team499;
  using team499::degrees;

  vex::thread taskThread(runTasks);

  /*
      - Set up robot
      - Score at ball 0 bottom middle tower
  */
  
  // Set up robot and put ball 0 to top
  add(Intakes.SpinMotorsTo(30,400));
  add(SideRollers.SpinMotorsAt(100));
  add(Intakes.WaitUntilReaches(400));
  add(Intakes.SpinMotorsTo(100, 500));

  // drive forward a little
  driveForward(500, degrees);

  // point towards bottom middle tower
  turnTo(225);
  add(FlyWheel.SpinMotorsAt(30));
  add(Intakes.WaitUntilReaches(500));
  add(ready());

  // drive to bottom middle tower
  driveForward(700, degrees);

  // score ball 0 at bottom middle tower
  shoot();
  turnTo(225);

  // ---------- BOTTOM MIDDLE TOWER SCORED ----------

  /*
      - Collect ball 1
      - Score ball 1 at bottom left tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));

  // drive out of bottom middle tower / x-axis of ball 1
  driveForward(-700, degrees);

  // turn to ball 1
  turnTo(270);

  // pick up ball 1
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // drive to ball 1
  driveForward(2000, degrees);

  // point to bottom left tower
  turnTo(225);
  // move ball 1 to top and ready
  FlyWheel.SpinMotorsAt(30);
  add(Intakes.SpinMotorsTo(100, 800));
  add(Intakes.WaitUntilReaches(800));
  add(ready());

  // drive to bottom left tower
  driveForward(700, degrees);

  // score ball 1 at bottom left tower
  shoot();
  turnTo(225);

  // ---------- BOTTOM LEFT TOWER SCORED ----------

  /*
      - Collect ball 2
      - Score ball 2 at middle left tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));

  // drive out of bottom left tower / y-axis of ball 2
  driveForward(-1000, degrees);

  // turn to ball 2
  turnTo(0);

  // pick up ball 2
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // drive to ball 2 / x-axis of middle left tower
  driveForward(2500, degrees);
  
  // point to middle left tower
  turnTo(270);
  // move ball 1 to top and ready
  FlyWheel.SpinMotorsAt(30);
  add(Intakes.SpinMotorsTo(100, 800));
  add(Intakes.WaitUntilReaches(800));
  add(ready());

  // drive to middle left tower
  driveForward(700, degrees);

  // score ball 2 at middle left tower
  shoot();
  turnTo(270);

  // ---------- MIDDLE LEFT TOWER SCORED ----------

  /*
      - Collect ball 3
      - Score ball 3 at top left tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));

  // drive out of middle left tower / y-axis of ball 3
  driveForward(-1500, degrees);

  // turn to ball 3
  turnTo(0);

  // pick up ball 3
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // drive to ball 3
  driveForward(2500, degrees);
  
  // point to top left tower
  turnTo(315);
  // move ball 3 to top and ready
  FlyWheel.SpinMotorsAt(30);
  add(Intakes.SpinMotorsTo(100, 800));
  add(Intakes.WaitUntilReaches(800));
  add(ready());

  // drive to top left tower
  driveForward(700, degrees);

  // score ball 3 at top left tower
  shoot();
  turnTo(315);

  // ---------- TOP LEFT TOWER SCORED ----------

  /*
      - Collect ball 4
      - Score ball 4 at top middle tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));

  // drive out of top left tower
  driveForward(-1500, degrees);

  // turn to ball 4
  turnTo(135);

  // pick up ball 4
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // drive to ball 4 / x-axis of top middle tower
  driveForward(1500, degrees);
  
  // point to top middle tower
  turnTo(0);
  // move ball 4 to top and ready
  FlyWheel.SpinMotorsAt(30);
  add(Intakes.SpinMotorsTo(100, 800));
  add(Intakes.WaitUntilReaches(800));
  add(ready());

  // drive to top middle tower
  driveForward(1500, degrees);

  // score ball 4 at top middle tower
  shoot();
  turnTo(0);

  // ---------- TOP MIDDLE TOWER SCORED ----------

  // TOP RIGHT TOWER IS THE SAME AS BOTTOM LEFT TOWER

  /*
      - Collect ball 5
      - Score ball 5 at top right tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));

  // drive out of top middle tower / x-axis of ball 5
  driveForward(-700, degrees);

  // turn to ball 5
  turnTo(90);

  // pick up ball 5
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // drive to ball 5
  driveForward(2000, degrees);

  // point to top right tower
  turnTo(45);
  // move ball 5 to top and ready
  FlyWheel.SpinMotorsAt(30);
  add(Intakes.SpinMotorsTo(100, 800));
  add(Intakes.WaitUntilReaches(800));
  add(ready());

  // drive to top right tower
  driveForward(700, degrees);

  // score ball 5 at top right tower
  shoot();
  turnTo(45);

  // ---------- TOP RIGHT TOWER SCORED ----------

  // MIDDLE RIGHT TOWER IS THE SAME AS MIDDLE LEFT TOWER

  /*
      - Collect ball 6
      - Score ball 6 at middle right tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));

  // drive out of top right tower / y-axis of ball 6
  driveForward(-1000, degrees);

  // turn to ball 6
  turnTo(180);

  // pick up ball 6
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // drive to ball 6 / x-axis of middle right tower
  driveForward(2500, degrees);
  
  // point to middle right tower
  turnTo(90);
  // move ball 6 to top and ready
  FlyWheel.SpinMotorsAt(30);
  add(Intakes.SpinMotorsTo(100, 800));
  add(Intakes.WaitUntilReaches(800));
  add(ready());

  // drive to middle right tower
  driveForward(700, degrees);

  // score ball 6 at middle right tower
  shoot();
  turnTo(90);

  // ---------- MIDDLE RIGHT TOWER SCORED ----------

  // BOTTOM RIGHT TOWER IS THE SAME AS TOP LEFT TOWER

  /*
      - Collect ball 7
      - Score ball 7 at bottom right tower
  */

  // get rid of blue ball
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -2000));

  // drive out of middle right tower / y-axis of ball 7
  driveForward(-1500, degrees);

  // turn to ball 7
  turnTo(180);

  // pick up ball 7
  add(SideRollers.WaitUntilReaches(-2000));
  add(SideRollers.SpinMotorsAt(100));

  // drive to ball 7
  driveForward(2500, degrees);
  
  // point to bottom right tower
  turnTo(45);
  // move ball 3 to top and ready
  FlyWheel.SpinMotorsAt(30);
  add(Intakes.SpinMotorsTo(100, 800));
  add(Intakes.WaitUntilReaches(800));
  add(ready());

  // drive to bottom right tower
  driveForward(700, degrees);

  // score ball 7 at bottom right tower
  shoot();

  // drive out and get rid of all
  driveForward(-1000, degrees);
  Intakes.SpinMotorsTo(-100, -1200);
  SideRollers.SpinMotorsTo(-70, -3000);

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