//
// Created by Jakub Gert on 06/06/2020.
//

#ifndef GRBL_LINENUMBERPARSER_H
#define GRBL_LINENUMBERPARSER_H


#include <string>

using namespace std;

class LineNumberParser {
private:
    int value;
public:
    bool parse(const string &message);
    int getLineNumber() const;
};


#endif //GRBL_LINENUMBERPARSER_H
