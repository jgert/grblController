//
// Created by Jakub Gert on 07/05/2021.
//

#ifndef MACHINE_PARSER_H
#define MACHINE_PARSER_H

#include "src/gCode/Parser.h"
#include "MachineState.h"

namespace machine {

    float convertToMetricsIfNeeded(const MachineState &currentState, float value);

    bool G00(const gCode::Block &block, const MachineState &currentState, MachineState &nextState);

    bool G01(const gCode::Block &block, const MachineState &currentState, MachineState &nextState);

    bool G02_G03(const gCode::Block &block, const MachineState &currentState, MachineState &nextState);

    bool G17(const gCode::Block &block, MachineState &nextState);

    bool G18(const gCode::Block &block, MachineState &nextState);

    bool G19(const gCode::Block &block, MachineState &nextState);

    bool G20(const gCode::Block &block, MachineState &nextState);

    bool G21(const gCode::Block &block, MachineState &nextState);

    bool G90(const gCode::Block &block, MachineState &nextState);

    bool G91(const gCode::Block &block, MachineState &nextState);
}

#endif //MACHINE_PARSER_H
