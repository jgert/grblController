//
// Created by Jakub Gert on 07/06/2020.
//

#include <regex>
#include <string>
#include "InputPinStateParser.h"

using namespace std;

bool InputPinStateParser::parse(const string &message) {

    static regex r("^Pn:([XYZPDHRS]+)$");

    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    InputPinState state;
    string s = cm[1].str();
    for (char it : s) {
        switch (it) {
            case 'X':
                state.xLimit = true;
                break;
            case 'Y':
                state.yLimit = true;
                break;;
            case 'Z':
                state.zLimit = true;
                break;
            case 'P':
                state.probe = true;
                break;
            case 'D':
                state.door = true;
                break;
            case 'H':
                state.hold = true;
                break;
            case 'R':
                state.softReset = true;
                break;;
            case 'S':
                state.cycleStart = true;
                break;
            default:
                return false;
        }
    }

    inputPinState = state;
    return true;
}

InputPinState InputPinStateParser::getInputPinState() const {
    return inputPinState;
}

InputPinState::InputPinState() :
        xLimit(false),
        yLimit(false),
        zLimit(false),
        probe(false),
        door(false),
        hold(false),
        softReset(false),
        cycleStart(false) {

}
