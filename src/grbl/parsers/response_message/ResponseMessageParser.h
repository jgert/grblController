//
// Created by Jakub Gert on 20/06/2020.
//

#ifndef GRBL_RESPONSEMESSAGEPARSER_H
#define GRBL_RESPONSEMESSAGEPARSER_H

#include <string>

using namespace std;

class ResponseMessageParser {
public:
    enum Result {
        Ok,
        Error
    };

private:
    unsigned int error;
    Result result;

public:
    bool parse(const string &message);

    Result getResult() const;
    unsigned int getError() const;
};

#endif //GRBL_RESPONSEMESSAGEPARSER_H
