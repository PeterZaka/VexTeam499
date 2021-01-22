#pragma once

#include "vex.h"
#include <vector>

namespace team499{

  extern std::vector<void (*)()> tasks;

  void runTasks();
}