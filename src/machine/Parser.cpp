//
// Created by Jakub Gert on 07/05/2021.
//

#include "Engraver3axis.h"

namespace machine {

    float convertToMetricsIfNeeded(const MachineState &currentState, float value) {
        if (currentState.units == MachineState::Imperial) {
            return value * 25.4f;
        } else {
            return value;
        }
    }

}
