//
// Created by Jakub Gert on 10/06/2020.
//

#ifndef GRBL_ALARMPARSER_H
#define GRBL_ALARMPARSER_H

#include <string>

using namespace std;

class AlarmParser {
    unsigned int value;
public:
    bool parse(const string &message);
    unsigned int getAlarmValue() const;
};


#endif //GRBL_ALARMPARSER_H
