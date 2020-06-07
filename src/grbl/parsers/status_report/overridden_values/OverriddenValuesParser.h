//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef GRBL_OVERRIDDENVALUESPARSER_H
#define GRBL_OVERRIDDENVALUESPARSER_H

#include <string>

using namespace std;

struct OverriddenValues {
    unsigned int feed;
    unsigned int rapid;
    unsigned int spindle;
};

class OverriddenValuesParser {
    OverriddenValues values;
public:
    bool parse(const string &message);

    OverriddenValues getOverriddenValues() const;
};

#endif //GRBL_OVERRIDDENVALUESPARSER_H
