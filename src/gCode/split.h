//
// Created by Jakub Gert on 03/10/2020.
//

#ifndef GRBL_SPLIT_H
#define GRBL_SPLIT_H

#include <string>

using namespace std;

namespace gCode {
    vector<string> splitByNewLine(const string& s);
}

#endif //GRBL_SPLIT_H
