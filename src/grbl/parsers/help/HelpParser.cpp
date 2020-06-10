//
// Created by Jakub Gert on 10/06/2020.
//

#include <regex>
#include <iostream>
#include "HelpParser.h"

bool HelpParser::parse(const string &message) {

    static regex r1(R"(^\[HLP:(.*)\]$)");
    static regex r2(R"(([^\s\]]+))");

    std::smatch cm1;

    if (!regex_match(message, cm1, r1)) {
        return false;
    }
    smatch sm;
    string captured = cm1.str();
    if (regex_search(captured, sm, r2)) {
        for (size_t i = 1; i < sm.size(); i++) {
            cout << sm[i] << endl;
        }
    }

    string content = cm1[1];

    std::smatch cm2;
    helpOptions.clear();
    while (regex_search(content, cm2, r2)) {
        helpOptions.push_back(cm2[0]);
        content = cm2.suffix();
    }

    return true;
}

const vector<string> &HelpParser::getHelpOptions() const {
    return helpOptions;
}
