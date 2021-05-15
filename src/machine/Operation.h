//
// Created by Jakub Gert on 07/05/2021.
//

#ifndef GRBL_OPERATION_H
#define GRBL_OPERATION_H

#include <QVector3D>

namespace machine {

    struct OperationMove {
        QVector3D from;
        QVector3D to;
        float speed;

        explicit OperationMove(QVector3D from, QVector3D to, float speed);
        explicit OperationMove();
    };

    inline bool operator==(const OperationMove &lhs, const OperationMove &rhs) {
        return lhs.from == rhs.from && lhs.to == rhs.to && lhs.speed == rhs.speed;
    }

    struct OperationArc {
        QVector3D from;
        QVector3D to;
        QVector3D center;
        float radius;
        uint8_t axis_0;
        uint8_t axis_1;
        uint8_t axis_linear;
        bool clockwise;
        float feedRate;

        explicit OperationArc();
        explicit OperationArc(
                QVector3D from,
                QVector3D to,
                QVector3D center,
                float radius,
                uint8_t axis_0,
                uint8_t axis_1,
                uint8_t axis_linear,
                bool clockwise,
                float feedRate);
    };

    inline bool operator==(const OperationArc &lhs, const OperationArc &rhs) {
        bool conditions[] = {
                lhs.from == rhs.from,
                lhs.to == rhs.to,
                lhs.center == rhs.center,
                lhs.radius == rhs.radius,
                lhs.axis_0 == rhs.axis_0,
                lhs.axis_1 == rhs.axis_1,
                lhs.axis_linear == rhs.axis_linear,
                lhs.clockwise == rhs.clockwise,
                lhs.feedRate == rhs.feedRate
        };
        bool result = true;
        for(auto c : conditions) {
            result &= c;
        }
        return result;
    };

    struct Operation {
        enum Type {
            NoOperation,
            Move,
            Arc
        };
        Type type = NoOperation;
        OperationMove operationMove;
        OperationArc operationArc;

        explicit Operation();

        Operation(const Operation &operation) = default;

        explicit Operation(OperationMove move);
        explicit Operation(OperationArc arc);
    };

    inline bool operator==(const Operation &lhs, const Operation &rhs) {
        return lhs.type == rhs.type && lhs.operationMove == rhs.operationMove && lhs.operationArc == rhs.operationArc;
    }

}

#endif //GRBL_OPERATION_H
