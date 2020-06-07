//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef GRBL_INPUTPINSTATEPARSER_H
#define GRBL_INPUTPINSTATEPARSER_H

#include <string>

using namespace std;

struct InputPinState {
    bool xLimit;
    bool yLimit;
    bool zLimit;
    bool probe;
    bool door;
    bool hold;
    bool softReset;
    bool cycleStart;

    InputPinState();

    friend inline bool operator==(const InputPinState &v1, const InputPinState &v2) {

        bool result = true;

        result &= v1.xLimit == v2.xLimit;
        result &= v1.yLimit == v2.yLimit;
        result &= v1.zLimit == v2.zLimit;
        result &= v1.probe == v2.probe;
        result &= v1.door == v2.door;
        result &= v1.hold == v2.hold;
        result &= v1.softReset == v2.softReset;
        result &= v1.cycleStart == v2.cycleStart;

        return  result;
    }
};

class InputPinStateParser {
    InputPinState inputPinState;
public:
    bool parse(const string &message);
    InputPinState getInputPinState() const;
};


#endif //GRBL_INPUTPINSTATEPARSER_H
