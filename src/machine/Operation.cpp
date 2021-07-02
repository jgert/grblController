//
// Created by Jakub Gert on 07/05/2021.
//

#include "Operation.h"

namespace machine {

    OperationMove::OperationMove() :
            from(QVector3D()),
            to(QVector3D()),
            speed(0.0f) {
    }

    OperationMove::OperationMove(QVector3D from, QVector3D to, float speed) :
            from(from),
            to(to),
            speed(speed) {
    }

    OperationArc::OperationArc() :
            from(QVector3D()),
            to(QVector3D()),
            center(QVector3D()),
            radius(0.0f),
            axis_0(0),
            axis_1(1),
            axis_linear(2),
            clockwise(false),
            feedRate(0.0f) {

    }

    OperationArc::OperationArc(
            QVector3D from,
            QVector3D to,
            QVector3D center,
            float radius,
            uint8_t axis_0,
            uint8_t axis_1,
            uint8_t axis_linear,
            bool clockwise,
            float feedRate) :
            from(from),
            to(to),
            center(center),
            radius(radius),
            axis_0(axis_0),
            axis_1(axis_1),
            axis_linear(axis_linear),
            clockwise(clockwise),
            feedRate(feedRate) {

    }

    Operation::Operation(OperationMove move) :
            type(Move),
            operationMove(move) {

    }

    Operation::Operation(OperationArc arc) :
            type(Arc),
            operationArc(arc) {

    }

    Operation::Operation() :
            type(NoOperation) {

    }
}
