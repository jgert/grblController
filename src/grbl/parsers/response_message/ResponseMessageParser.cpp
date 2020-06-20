//
// Created by Jakub Gert on 20/06/2020.
//

#include <regex>
#include "ResponseMessageParser.h"

bool ResponseMessageParser::parse(const string &message) {

    if (message=="ok") {
        error = 0;
        result = Ok;
        return true;
    } else {

        static regex r("^(error):([0-9]+)$");

        std::smatch cm;

        if (!regex_match(message, cm, r)) {
            return false;
        }

        error = stoi(cm[2]);
        result = Error;

        return true;
    }
}

unsigned int ResponseMessageParser::getError() const {
    return error;
}

ResponseMessageParser::Result ResponseMessageParser::getResult() const {
    return result;
}
