//
// Created by Jakub Gert on 05/06/2020.
//

#ifndef GRBL_POSITIONPARSER_H
#define GRBL_POSITIONPARSER_H

#include <string>
#include <src/grbl/vec3/vec3.h>

using namespace std;

class PositionParser {
private:
    typedef enum {
        wpos = 0,
        mpos
    } LastRead;

    vec3 machinePosition;
    vec3 workPosition;
    vec3 workCoordinateOffset;
    LastRead  lastRead;
public:

    bool parse(const string &message);

    vec3 getMachinePosition() const;

    vec3 getWorkPosition() const;

    vec3 getWorkCoordinateOffset() const;
};


#endif //GRBL_POSITIONPARSER_H
