#pragma once

/*

- Use std::function instead of function pointer
- Make class in order for more than two things to move separately

*/

#include "vex.h"
#include <vector>

namespace team499{

  extern std::vector<void (*)()> tasks;

  void runTasks();
}