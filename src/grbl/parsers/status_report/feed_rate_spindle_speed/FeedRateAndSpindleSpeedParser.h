//
// Created by Jakub Gert on 06/06/2020.
//

#ifndef GRBL_FEEDRATEANDSPINDLESPEEDPARSER_H
#define GRBL_FEEDRATEANDSPINDLESPEEDPARSER_H

#include <string>

using namespace std;

class FeedRateAndSpindleSpeedParser {
private:
    int feedRate;
    int spindleSpeed;
public:
    bool parse(const string &message);
    int getFeedRate() const;
    int getSpindleSpeed() const;
};

#endif //GRBL_FEEDRATEANDSPINDLESPEEDPARSER_H
