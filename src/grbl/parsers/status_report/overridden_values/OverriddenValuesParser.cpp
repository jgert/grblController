//
// Created by Jakub Gert on 07/06/2020.
//

#include <regex>
#include "OverriddenValuesParser.h"

bool OverriddenValuesParser::parse(const string &message) {

    static regex r("^Ov:([0-9]+),([0-9]+),([0-9]+)$");

    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    values.feed = stoi(cm[1].str());
    values.rapid = stoi(cm[2].str());
    values.spindle = stoi(cm[3].str());

    return true;
}

OverriddenValues OverriddenValuesParser::getOverriddenValues() const {
    return values;
}
