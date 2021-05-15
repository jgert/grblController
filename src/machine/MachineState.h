//
// Created by Jakub Gert on 07/05/2021.
//

#ifndef GRBL_MACHINE_STATE_H
#define GRBL_MACHINE_STATE_H

#include "Operation.h"
#include "Error.h"

namespace machine {

    struct MachineState {

        typedef enum {
            Absolute,
            Incremental
        } CoordinateMode;

        typedef enum {
            Imperial,
            Metric,
        } Units;

        typedef enum {
            XY,
            ZX,
            YZ
        } PlaneSelection;

        Units units = Metric;
        QVector3D currentPosition;
        CoordinateMode coordinateMode = Absolute;
        PlaneSelection planeSelection = XY;
        float feedRate = -1;
        unsigned int programLineNumber = 0;
        unsigned int sourceLineNumber = 0;
        unsigned int lastGCodeCommand = 0;
        unsigned int lastGCodeSubcommand = 0;
        Operation operation = Operation();
        Error error = Error();

        MachineState() = default;

        MachineState(const MachineState &state) = default;
    };

}

#endif //GRBL_MACHINE_STATE_H
