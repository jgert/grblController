//
// Created by Jakub Gert on 04/06/2020.
//

#ifndef GRBL_MACHINESTATEPARSER_H
#define GRBL_MACHINESTATEPARSER_H

#include <string>

using namespace std;

typedef enum State {
    Idle,
    Run,
    Hold,
    Jog,
    Alarm,
    Door,
    Check,
    Home,
    Sleep
} State;

typedef int Code;

struct MachineState {
    explicit MachineState();

    explicit MachineState(State state, Code code);

    State state;
    Code code;
};

class MachineStateParser {
private:
    MachineState machineState;
public:
    bool parse(const string &message);
    MachineState getMachineState() const;
};


#endif //GRBL_MACHINESTATEPARSER_H
