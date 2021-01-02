#pragma once

#include "motorGroup.h"

class controllerInput
{
private:
  bool (*input)();
  std::vector<motorGroup*> positiveGroups;
  std::vector<motorGroup*> negativeGroups;
public:
  controllerInput(
    bool (*inputFunc)(),
    const std::vector<motorGroup*>& positiveGroups,
    const std::vector<motorGroup*>& negativeGroups = {});
  void updateButton();
};