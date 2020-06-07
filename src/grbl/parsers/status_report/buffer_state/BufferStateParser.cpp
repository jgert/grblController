//
// Created by Jakub Gert on 06/06/2020.
//

#include <string>
#include <regex>
#include "BufferStateParser.h"

using namespace std;

bool BufferStateParser::parse(const string &status) {

    static regex r("^Bf:([0-9]+),([0-9]+)$");
    std::smatch cm;

    if (!regex_match(status, cm, r)) {
        return false;
    }

    state.availableBlocks = stoi(cm[1].str());
    state.availableBytesInRxBuffer = stoi(cm[2].str());

    return true;
}

BufferState BufferStateParser::getBufferState() const {
    return state;
}
