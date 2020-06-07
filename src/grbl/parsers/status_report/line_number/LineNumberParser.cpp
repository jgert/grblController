//
// Created by Jakub Gert on 06/06/2020.
//

#include <string>
#include <regex>
#include "LineNumberParser.h"

using namespace std;

bool LineNumberParser::parse(const string &message) {

    static string intPattern("[-+]?[0-9]+");
    static string pattern("^Ln:(" + intPattern + ")$");
    static regex r(pattern);

    std::smatch cm;
    if (!regex_match(message, cm, r)) {
        return false;
    }

    value = stoi(cm[1].str());

    return true;
}

int LineNumberParser::getLineNumber() const {
    return value;
}
