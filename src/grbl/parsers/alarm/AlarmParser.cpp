//
// Created by Jakub Gert on 10/06/2020.
//

#include <regex>
#include "AlarmParser.h"

bool AlarmParser::parse(const string &message) {

    static regex r("^ALARM:([0-9]+)$");

    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    value = stoi(cm[1].str());

    return true;
}

unsigned int AlarmParser::getAlarmValue() const {
    return value;
}
