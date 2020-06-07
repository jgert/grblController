//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef GRBL_FEEDRATEPARSER_H
#define GRBL_FEEDRATEPARSER_H

#include <string>

using namespace std;

class FeedRateParser {
private:
    int feedRate;
public:
    bool parse(const string &message);
    int getFeedRate() const;
};

#endif //GRBL_FEEDRATEPARSER_H
