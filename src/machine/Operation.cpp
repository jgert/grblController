//
// Created by Jakub Gert on 07/05/2021.
//

#include "Operation.h"

namespace machine {

    OperationMove::OperationMove(QVector3D from, QVector3D to, float speed) :
            from(from),
            to(to),
            speed(speed) {

    }

    Operation::Operation(OperationMove move) :
            type(Move),
            operationMove(move) {

    }

    Operation::Operation() :
            type(NoOperation),
            operationMove(QVector3D(), QVector3D(), 0.0f) {

    }

}
