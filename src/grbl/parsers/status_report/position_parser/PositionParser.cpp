//
// Created by Jakub Gert on 05/06/2020.
//

#include <regex>
#include <string>
#include "PositionParser.h"

using namespace std;

vec3 PositionParser::getMachinePosition() const {
    return machinePosition;
}

vec3 PositionParser::getWorkPosition() const {
    return workPosition;
}

vec3 PositionParser::getWorkCoordinateOffset() const {
    return workCoordinateOffset;
}

bool PositionParser::parse(const string &message) {

    static string mpos("MPos");
    static string wpos("WPos");
    static string wco("WCO");

    static string patternFloat("([-+]?[0-9]*\\.?[0-9]+)");
    static string pattern(
            "^("
            + mpos
            + "|"
            + wpos
            + "|"
            + wco
            + "):"
            + patternFloat + "," + patternFloat + "," + patternFloat + "$");

    static regex r(pattern);
    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    float x = stof(cm[2].str());
    float y = stof(cm[3].str());
    float z = stof(cm[4].str());

    vec3 pos(x, y, z);

    if (cm[1].str() == mpos) {
        machinePosition = pos;
        workPosition = machinePosition - workCoordinateOffset;
        lastRead = LastRead::mpos;
    } else if (cm[1].str() == wpos) {
        workPosition = pos;
        machinePosition = workPosition + workCoordinateOffset;
        lastRead = LastRead::wpos;
    } else if (cm[1].str() == wco) {
        workCoordinateOffset = pos;
        switch (lastRead) {
            case LastRead::wpos:
                machinePosition = workPosition + workCoordinateOffset;
                break;
            case LastRead::mpos:
                workPosition = machinePosition - workCoordinateOffset;
                break;
        }
    }

    return true;
}
