//
// Created by Jakub Gert on 06/06/2020.
//

#include <regex>
#include <string>
#include "FeedRateAndSpindleSpeedParser.h"

using namespace std;

bool FeedRateAndSpindleSpeedParser::parse(const string &message) {
    static regex r("^FS:([0-9]+),([0-9]+)$");

    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    feedRate = stoi(cm[1].str());
    spindleSpeed = stoi(cm[2].str());

    return true;
}

int FeedRateAndSpindleSpeedParser::getFeedRate() const {
    return feedRate;
}

int FeedRateAndSpindleSpeedParser::getSpindleSpeed() const {
    return spindleSpeed;
}
