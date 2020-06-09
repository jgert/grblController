//
// Created by Jakub Gert on 08/06/2020.
//

#ifndef GRBL_WELCOMEMESSAGEPARSER_H
#define GRBL_WELCOMEMESSAGEPARSER_H

#include <string>

using namespace std;

class WelcomeMessageParser {
    string version;
public:
    bool parse(const string &message);
    string getVersion() const;
};


#endif //GRBL_WELCOMEMESSAGEPARSER_H
