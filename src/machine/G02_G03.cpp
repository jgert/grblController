//
// Created by Jakub Gert on 07/05/2021.
//

#include <cmath>
#include <QVector2D>
#include "Parser.h"

using namespace gCode;

namespace machine {

    bool G02_G03(const gCode::Block &block, const MachineState &currentState, MachineState &nextState) {

        if (block.chunks.empty()) {
            nextState.error = Error(block.lineNumber, Error::MissingArguments);
            return false;
        }

        const auto &command = block.chunks[0];

        if (command.type != Chunk::Type::Command) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandChunkType);
            return false;
        }

        if ((command.command != 2 && command.command != 3) || command.subcommand != 0) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandNumber);
            return false;
        }

        QVector3D startPoint = currentState.currentPosition;
        QVector3D endPoint = startPoint;
        QVector3D ijk = QVector3D(0, 0, 0);
        bool ijk_set[3] = { false, false, false };
        float radius = NAN;

        for (size_t a = 1; a < block.chunks.size(); a++) {
            const auto &chunk = block.chunks[a];

            if (chunk.type != gCode::Chunk::Type::Address) {
                nextState.error = Error(block.lineNumber, Error::UnexpectedChunkType);
                return false;
            }

            switch (chunk.address) {
                case 'F':
                    nextState.feedRate = chunk.value;
                    break;
                case 'I':
                    ijk.setX(convertToMetricsIfNeeded(currentState, chunk.value));
                    ijk_set[0] = true;
                    break;
                case 'J':
                    ijk.setY(convertToMetricsIfNeeded(currentState, chunk.value));
                    ijk_set[1] = true;
                    break;
                case 'K':
                    ijk.setZ(convertToMetricsIfNeeded(currentState, chunk.value));
                    ijk_set[2] = true;
                    break;
                case 'R':
                    radius = convertToMetricsIfNeeded(currentState, chunk.value);
                    break;
                case 'X':
                    endPoint.setX(convertToMetricsIfNeeded(currentState, chunk.value));
                    break;
                case 'Y':
                    endPoint.setY(convertToMetricsIfNeeded(currentState, chunk.value));
                    break;
                case 'Z':
                    endPoint.setZ(convertToMetricsIfNeeded(currentState, chunk.value));
                    break;
                default:
                    nextState.error = Error(block.lineNumber, Error::InvalidAddress);
                    return false;
            }
        }

        if (currentState.coordinateMode == MachineState::Incremental) {
            for (int a = 0; a < 3; a++) {
                endPoint[a] = startPoint[a] + endPoint[a];
            }
        }

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

        int axis_0;
        int axis_1;
        int axis_linear;

        switch (currentState.planeSelection) {
            case MachineState::XY:
                axis_0 = AXIS_X;
                axis_1 = AXIS_Y;
                axis_linear = AXIS_Z;
                break;
            case MachineState::YZ:
                axis_0 = AXIS_Y;
                axis_1 = AXIS_Z;
                axis_linear = AXIS_X;
                break;
            case MachineState::ZX:
                axis_0 = AXIS_Z;
                axis_1 = AXIS_X;
                axis_linear = AXIS_Y;
                break;
        }

        float x = endPoint[axis_0] - currentState.currentPosition[axis_0];
        float y = endPoint[axis_1] - currentState.currentPosition[axis_1];

        if (!std::isnan(radius)) {

            auto delta = startPoint - endPoint;
            if (delta.lengthSquared() == 0) {
                nextState.error = Error(block.lineNumber, Error::InvalidTarget);
                return false;
            }

            float h_x2_div_d = 4.0f * powf(radius, 2.0f) - powf(x, 2.0f) - powf(y, 2.0f);
            if (h_x2_div_d < 0) {
                nextState.error = Error(block.lineNumber, Error::ArcRadius);
                return false;
            }
            h_x2_div_d = -sqrt(h_x2_div_d) / hypot(x, y);

            if (command.command == 3) {
                h_x2_div_d = -h_x2_div_d;
            }

            if (radius < 0) {
                h_x2_div_d = -h_x2_div_d;
                radius = -radius;
            }

            ijk[axis_0] = 0.5f*(x-(y*h_x2_div_d));
            ijk[axis_1] = 0.5f*(y+(x*h_x2_div_d));

            nextState.operation = Operation(OperationArc(
                    startPoint, endPoint, ijk,
                    radius,
                    axis_0,
                    axis_1,
                    axis_linear,
                    command.command == 2,
                    nextState.feedRate));
            return true;
        } else {
            if(!(ijk_set[axis_0] || ijk_set[axis_1])) {
                nextState.error = Error(block.lineNumber, Error::NoOffsetsInPlane);
                return false;
            }

            radius = hypot(ijk[axis_0], ijk[axis_1]);
            nextState.operation = Operation(OperationArc(
                    startPoint, endPoint, ijk,
                    radius,
                    axis_0,
                    axis_1,
                    axis_linear,
                    command.command == 2,
                    nextState.feedRate));
            return true;
        }
#undef AXIS_X
#undef AXIS_Y
#undef AXIS_Z
    }
}
