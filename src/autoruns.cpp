#include "autoruns.h"

#define add(x) team499::tasks.push_back([](){x;})
 
bool isReady = false;
 
/*
 
O        O        O
    3         5
*        4        *
 
O 2   *  O  *   6 O
  
*        8        *
    1         7
O        O #      O
 
*/
 
void autoSkills()
{
  using namespace team499;
  using team499::degrees;
 
  vex::thread taskThread(runTasks);
 
  vex::thread printThread(runPrints);
 
  // ---------- BOTTOM MIDDLE TOWER ----------

  /*
      - Set up robot
      - Score at ball 0 bottom middle tower
  */

  // Set up robot and put ball 0 to top
  add(Intakes.SpinMotorsTo(30, 400));
  add(SideRollers.SpinMotorsAt(100));
  add(Intakes.WaitUntilReaches(400));
  add(Intakes.SpinMotorsTo(100, 800));
 
  // drive forward a little
  driveForward(500, degrees);
 
  // point towards bottom middle tower
  turnTo(225);
  add(FlyWheel.SpinMotorsAt(50));
  add(Intakes.WaitUntilReaches(800));
  add(ready());
 
  // drive to bottom middle tower
  driveForward(650, degrees);
 
  // score ball 0 at bottom middle tower
  shoot();
 
  // ---------- BOTTOM LEFT TOWER ----------
 
  /*
      - Collect ball 1
      - Score ball 1 at bottom left tower
  */
 
  // get rid of blue ball
  emptyOut();
 
  // drive out of bottom middle tower / x-axis of ball 1
  driveForward(-600, degrees);
 
  // turn to ball 1
  turnTo(270);
 
  // pick up ball 1
  pickUpBall();
 
  // drive to ball 1
  driveForward(2700, degrees);
 
  // point to bottom left tower
  turnTo(225);
  isGuaranteed = true;
 
  // drive to bottom left tower
  driveForward(900, degrees);
 
  // score ball 1 at bottom left tower
  shoot();
 
  // ---------- MIDDLE LEFT TOWER ----------
 
  /*
      - Collect ball 2
      - Score ball 2 at middle left tower
  */
 
  // get rid of blue ball
  emptyOut();
 
  // drive out of bottom left tower / y-axis of ball 2
  driveForward(-600, degrees);
 
  // turn to ball 2
  turnTo(0);
 
  // pick up ball 2
  pickUpBall();
 
  // drive to ball 2 / x-axis of middle left tower
  driveForward(2100, degrees);
  
  // point to middle left tower
  turnTo(270);
  isGuaranteed = true;
 
  // drive to middle left tower
  driveForward(500, degrees);
 
  // descore once because it accidentally descores red
  SideRollers.SpinMotorsAt(0);
  SideRollers.SpinMotorsTo(100, 2500);

  // score ball 2 at middle left tower
  shoot();
 
  // ---------- TOP LEFT TOWER ----------
 
  /*
      - Collect ball 3
      - Score ball 3 at top left tower
  */
 
  // get rid of blue ball
  emptyOut();
 
  // drive out of middle left tower / y-axis of ball 3
  driveForward(-800, degrees);
 
  // turn to ball 3
  turnTo(0);
 
  // pick up ball 3
  pickUpBall();
 
  // drive to ball 3
  driveForward(1900, degrees);
  
  // point to top left tower
  turnTo(305);
  isGuaranteed = true;

  // drive to top left tower
  driveForward(1300, degrees);
 
  // score ball 3 at top left tower
  shoot();
 
  // ---------- TOP MIDDLE TOWER ----------
 
  /*
      - Collect ball 4
      - Score ball 4 at top middle tower
  */
 
  // get rid of blue ball
  emptyOut();
 
  // drive out of top left tower
  driveForward(-1500, degrees);
 
  maxPower = 80;
  // turn to ball 4
  turnTo(120);
  maxPower = 100;
 
  // pick up ball 4
  pickUpBall();
 
  // drive to ball 4 / y-axis of top middle tower
  driveForward(1600, degrees);
  
  // point to top middle tower
  turnTo(0);
  isGuaranteed = true;
 
  // drive to top middle tower
  driveForward(1600, degrees);
 
  // descore once because it accidentally descores red
  SideRollers.SpinMotorsAt(0);
  SideRollers.SpinMotorsTo(100, 2500);

  // score ball 4 at top middle tower
  shoot();
 
  // ---------- TOP RIGHT TOWER ----------
 
  /*
      - Collect ball 5
      - Score ball 5 at top right tower
  */
 
  // get rid of blue ball
  emptyOut();
 
  // drive out of top middle tower / x-axis of ball 5
  driveForward(-500, degrees);
 
  // turn to ball 5
  turnTo(90);
 
  // pick up ball 5
  pickUpBall();
 
  // drive to ball 5
  driveForward(2150, degrees);
 
  // point to top right tower
  turnTo(45);
  isGuaranteed = true;
 
  // drive to top right tower
  driveForward(950, degrees);
 
  // score ball 5 at top right tower
  shoot();
 
  // ---------- MIDDLE RIGHT TOWER ----------
 
  // MIDDLE RIGHT TOWER IS THE SAME AS MIDDLE LEFT TOWER
 
  /*
      - Collect ball 6
      - Score ball 6 at middle right tower
  */
 
  // get rid of blue ball
  emptyOut();
 
  // drive out of top right tower / y-axis of ball 6
  driveForward(-600, degrees);  // was -800
 
  // turn to ball 6
  turnTo(180);
 
  // pick up ball 6
  pickUpBall();
 
  // drive to ball 6 / x-axis of middle right tower
  driveForward(2100, degrees); // was 2000
  
  // point to middle right tower
  turnTo(90);
  isGuaranteed = true;
 
  // drive to middle right tower
  driveForward(500, degrees);
 
  // descore once because it accidentally descores red
  SideRollers.SpinMotorsAt(0);
  SideRollers.SpinMotorsTo(100, 2500);

  // score ball 6 at middle right tower
  shoot();
 
  // ---------- BOTTOM RIGHT TOWER ----------
 
  // BOTTOM RIGHT TOWER IS THE SAME AS TOP LEFT TOWER
 
  /*
      - Collect ball 7
      - Score ball 7 at bottom right tower
  */
 
  // get rid of blue ball
  emptyOut();
 
  // drive out of middle right tower / y-axis of ball 7
  driveForward(-800, degrees);
 
  // turn to ball 7
  turnTo(180);
 
  // pick up ball 7
  pickUpBall();
 
  // drive to ball 7
  driveForward(1900, degrees);
  
  // point to bottom right tower
  turnTo(125);
  isGuaranteed = true;
 
  // drive to bottom right tower
  driveForward(1300, degrees);
 
  // score ball 7 at bottom right tower
  shoot();
 
  // ---------- MIDDLE TOWER ----------
 
  // MIDDLE TOWER IS SIMMILAR TO TOP MIDDLE TOWER
 
  /*
      - Collect ball 8
      - Score ball 8 at middle tower
  */
  
  // get rid of blue ball
  emptyOut();
 
  // drive out of bottom right tower
  driveForward(-1500, degrees);
 
  maxPower = 80;
  // turn to ball 8
  turnTo(310);
  maxPower = 100;
 
  // pick up ball 8
  pickUpBall();
 
  // drive to ball 8 / left sideroller of y-axis of middle tower
  driveForward(1500, degrees);
  
  // point to middle tower
  turnTo(0);
  isGuaranteed = true;
 
  // drive to middle tower and descore one
  driveForward(1000, degrees);

  driveForward(-500, degrees);
  driveForward(400, degrees);

  turnTo(340);

  // score ball 8 at middle tower
  shoot();
 
  taskThread.interrupt();
 
}
 
void shoot()
{
  // wait until intakes are ready
  waitUntil(isReady);
  isReady = false; 

  // shoot ball
  Intakes.SpinMotorsTo(100, 250);
  Intakes.WaitUntilReaches(250);

  // adjust back and wait min 0.5 sec
  add(wait(0.75, sec));
  add(ready());
  team499::turnTo(team499::targetRot);

  // continue when done
  waitUntil(isReady);
  FlyWheel.Stop();
  isReady = false;
  isGuaranteed = false;
}

void pickUpBall()
{
  // siderollers in
  add(SideRollers.SpinMotorsAt(100));

  // wait until vision detects red in intake
  add(waitUntilRed());

  // start flywheel, move ball up, ready
  add(FlyWheel.SpinMotorsAt(40));
  add(Intakes.SpinMotorsTo(100, 1200));
  add(Intakes.WaitUntilReaches(1200));
  add(ready());
}

void emptyOut()
{
  // wait until out of tower then empty
  LeftWheel.ResetEncoders();
  add(LeftWheel.WaitUntilReaches(-300));
  add(Intakes.SpinMotorsTo(-100, -600));
  add(SideRollers.SpinMotorsTo(-70, -1000));
  add(wait(1, sec));
}

void ready()
{
  isReady = true;
}