//
// Created by Jakub Gert on 03/10/2020.
//

#include <sstream>
#include <vector>
#include <regex>
#include "split.h"

namespace gCode {

    vector<string> splitByPattern(const string &s, const regex &pattern) {
        vector<string> items;
        copy(sregex_token_iterator(s.begin(), s.end(), pattern, -1),
             sregex_token_iterator(), back_inserter(items));
        return items;
    }

    vector<string> splitByNewLine(const string &s) {
        return splitByPattern(s, regex("(\n)|(\r\n)"));
    }
}
