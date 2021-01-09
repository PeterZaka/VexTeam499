#include "autoruns.h"

void autoSkills()
{
  using namespace team499;
  using team499::degrees;

  driveForward(4000, degrees);

  turnTo(90);

  turnTo(270);

  driveForward(500, degrees);

  driveForward(-500, degrees);

  turnTo(180);

  driveForward(4000, degrees);

  turnTo(0);

}