//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef GRBL_ACCESSORYSTATEPARSER_H
#define GRBL_ACCESSORYSTATEPARSER_H

#include <string>

using namespace std;

struct AccessoryState {
    enum SpindleState {
        off,
        enabledCW,
        enabledCCW,
    };

    SpindleState spindleState;
    bool floodCoolant;
    bool mistCoolant;

    AccessoryState();

    friend inline bool operator==(const AccessoryState &as1, const AccessoryState &as2) {
        bool result = true;
        result &= as1.floodCoolant == as2.floodCoolant;
        result &= as1.mistCoolant == as2.mistCoolant;
        result &= as1.spindleState == as2.spindleState;
        return result;
    }
};

class AccessoryStateParser {
    AccessoryState accessoryState;
public:
    bool parse(const string &message);
    AccessoryState getAccessoryState() const;
};


#endif //GRBL_ACCESSORYSTATEPARSER_H
