//
// Created by Jakub Gert on 08/06/2020.
//

#include <regex>
#include "WelcomeMessageParser.h"

bool WelcomeMessageParser::parse(const string &message) {

    static regex r(R"(Grbl (\d+.\d+\w*) (\[.*\]))");

    smatch cm;

    if(!regex_match(message, cm, r)) {
        return false;
    }

    version = cm[1].str();

    return true;
}

string WelcomeMessageParser::getVersion() const {
    return version;
}
