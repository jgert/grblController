//
// Created by Jakub Gert on 06/06/2020.
//

#include <regex>
#include <string>
#include "FeedRateParser.h"

using namespace std;

bool FeedRateParser::parse(const string &message) {

    static regex r("^F:([0-9]+)$");

    std::smatch cm;

    if (!regex_match(message, cm, r)) {
        return false;
    }

    feedRate = stoi(cm[1].str());

    return true;
}

int FeedRateParser::getFeedRate() const {
    return feedRate;
}
