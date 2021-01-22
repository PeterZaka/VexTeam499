#include "task.h"

namespace team499{

  std::vector<void (*)()> tasks;

  void runTasks()
  {
    while(true)
    {
      if(tasks.size() > 0)
      {
        tasks[0]();

        tasks.erase(tasks.begin());
      }
      
      wait(20, msec);
    }
  }

}