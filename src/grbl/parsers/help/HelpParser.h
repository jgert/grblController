//
// Created by Jakub Gert on 10/06/2020.
//

#ifndef GRBL_HELPPARSER_H
#define GRBL_HELPPARSER_H

#include <vector>
#include <string>

using namespace std;

class HelpParser {
private:
    vector<string> helpOptions;
public:
    bool parse(const string &message);
    const vector<string> &getHelpOptions() const;
};


#endif //GRBL_HELPPARSER_H
