//
// Created by Jakub Gert on 03/10/2020.
//

#include <sstream>
#include <vector>
#include <regex>
#include "split.h"

namespace gCode {

    size_t countMatchInRegex(const std::string &s, const regex &pattern)
    {
        auto words_begin = std::sregex_iterator(s.begin(), s.end(), pattern);
        auto words_end = std::sregex_iterator();
        return std::distance(words_begin, words_end);
    }

    vector<string> splitByPattern(const string &s, const regex &pattern) {
        vector<string> items;
        items.reserve(countMatchInRegex(s, pattern)+1);
        copy(sregex_token_iterator(s.begin(), s.end(), pattern, -1),
             sregex_token_iterator(), back_inserter(items));
        return items;
    }

    vector<string> splitByNewLine(const string &s) {
        return splitByPattern(s, regex("(\n)|(\r\n)"));
    }


}
