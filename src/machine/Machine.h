//
// Created by Jakub Gert on 22/10/2020.
//

#ifndef GRBL_MACHINE_H
#define GRBL_MACHINE_H

#include <QVector3D>
#include <vector>
#include "../gCode/Parser.h"
#include "Parser.h"

using namespace std;

namespace machine {

    class Machine {
    protected:
        MachineState initialState;
        vector<MachineState> states;
    public:

        enum ModalGroup {
            NonModalCode,
            Motion,
            PlaneSelection,
            DistanceMode,
            ArcIJKDistanceMode,
            FeedRateMode,
            Units,
            CutterDiameterCompensation,
            ToolLengthOffset,
            CannedCyclesReturnMode,
            CoordinateSystem,
            ControlMode,
            SpindleSpeedMode,
            LatheDiameterMode,

            Unknown,
        };

        explicit Machine(const MachineState &initialState);

        ModalGroup modalGroup(unsigned int command, unsigned int subcommand);

        virtual void reset() = 0;

        virtual bool parse(const vector<gCode::Block> &blocks) = 0;

        [[nodiscard]] const vector<MachineState> &getStates() const;

        [[nodiscard]] virtual const Error &error() const = 0;
    };

}

#endif //GRBL_MACHINE_H
