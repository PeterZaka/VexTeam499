#pragma once

#include "vex.h"
#include "auto.h"
#include "motors.h"
#include "task.h"
#include "vision.h"
#include "odom.h"

extern bool isReady;

void runPrints1();

void autoSkills();

void pickUpBall();

void shoot();

void emptyOut();

void ready();