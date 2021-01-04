#pragma once

#include "motorGroup.h"

namespace team499 {

    class controllerInput
    {
    public:

        controllerInput(
            bool (*inputFunc)(),
            const std::vector<motorGroup*>& positiveGroups,
            const std::vector<motorGroup*>& negativeGroups = {});

        void updateButton();


    private:

        bool (*input)();
        std::vector<motorGroup*> positiveGroups;
        std::vector<motorGroup*> negativeGroups;
    };
}