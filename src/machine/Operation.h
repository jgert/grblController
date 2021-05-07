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

        OperationMove(QVector3D from, QVector3D to, float speed);
    };

    inline bool operator==(const OperationMove &lhs, const OperationMove &rhs) {
        return lhs.from == rhs.from && lhs.to == rhs.to && lhs.speed == rhs.speed;
    }

    struct Operation {
        enum Type {
            NoOperation,
            Move
        };
        Type type = NoOperation;
        OperationMove operationMove;

        explicit Operation();

        Operation(const Operation &operation) = default;

        explicit Operation(OperationMove move);
    };

    inline bool operator==(const Operation &lhs, const Operation &rhs) {
        return lhs.type == rhs.type && lhs.operationMove == rhs.operationMove;
    }

}

#endif //GRBL_OPERATION_H
