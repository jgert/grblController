//
// Created by Jakub Gert on 04/06/2020.
//

#include <string>
#include <regex>
#include <map>
#include <vector>
#include "MachineStateParser.h"

using namespace std;

bool MachineStateParser::parse(const string &message) {

    static map <string, State> statesMap = {
            {"Idle",  State::Idle},
            {"Run",   State::Run},
            {"Hold",  State::Hold},
            {"Jog",   State::Jog},
            {"Alarm", State::Alarm},
            {"Door",  State::Door},
            {"Check", State::Check},
            {"Home",  State::Home},
            {"Sleep", State::Sleep},
    };

    static vector <regex> candidates = {
            regex("^(Idle)$"),
            regex("^(Run)$"),
            regex("^(Hold):([0-9]+)$"),
            regex("^(Hold)$"),
            regex("^(Jog)$"),
            regex("^(Alarm)$"),
            regex("^(Door):([0-9]+)?$"),
            regex("^(Door)$"),
            regex("^(Check)$"),
            regex("^(Home)$"),
            regex("^(Sleep)$"),
    };

    MachineState currentMachineState;

    for (auto &candidate : candidates) {
        std::smatch cm;
        if (!regex_match(message, cm, candidate)) {
            continue;
        }

        switch (cm.size()) {
            case 2:
                currentMachineState.state = statesMap[cm[1]];
                currentMachineState.code = -1;
                machineState = currentMachineState;
                return true;
            case 3:
                currentMachineState.state = statesMap[cm[1]];
                currentMachineState.code = stoi(cm[2]);
                machineState = currentMachineState;
                return true;
            default:
                continue;;
        }
    }
    return false;
}

MachineState MachineStateParser::getMachineState() const {
    return machineState;
}
