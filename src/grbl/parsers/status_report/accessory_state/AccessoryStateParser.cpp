//
// Created by Jakub Gert on 07/06/2020.
//

#include <string>
#include <regex>
#include "AccessoryStateParser.h"

using namespace std;

bool AccessoryStateParser::parse(const string &message) {

    static regex r("^A:([SCFM]+)$");

    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    AccessoryState state;
    string s = cm[1].str();
    for (char it : s) {
        switch (it) {
            case 'S':
                state.spindleState = AccessoryState::SpindleState::enabledCW;
                break;
            case 'C':
                state.spindleState = AccessoryState::SpindleState::enabledCCW;
                break;;
            case 'F':
                state.floodCoolant = true;
                break;;
            case 'M':
                state.mistCoolant = true;
                break;
            default:
                return false;
        }
    }

    accessoryState = state;
    return true;
}

AccessoryState AccessoryStateParser::getAccessoryState() const {
    return accessoryState;
}

AccessoryState::AccessoryState() :
        spindleState(off),
        floodCoolant(false),
        mistCoolant(false) {

}
