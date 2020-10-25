//
// Created by Jakub Gert on 22/10/2020.
//

#ifndef GRBL_MACHINE_H
#define GRBL_MACHINE_H

#include <QVector3D>
#include <vector>
#include "../gCode/Parser.h"

using namespace std;

struct OperationMove {
    QVector3D from;
    QVector3D to;
    float speed;

    OperationMove(QVector3D from, QVector3D to, float speed) : from(from), to(to), speed(speed) {}
};

struct Operation {
    enum Type {
        Move
    };
    Type type = Move;
    OperationMove operationMove;

    Operation(OperationMove move) : type(Move), operationMove(move) {}
};

inline bool operator==(const OperationMove &lhs, const OperationMove &rhs) {
    return (lhs.from == rhs.from) && (lhs.to == rhs.to) && (lhs.speed == rhs.speed);
};

inline bool operator==(const Operation &lhs, const Operation &rhs){
    return lhs.type == rhs.type && lhs.operationMove == rhs.operationMove;
};


class Machine {
protected:
    vector<Operation> operations;
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

    ModalGroup modalGroup(unsigned int command, unsigned int subcommand);

    const vector<Operation> &getOperations() const {
        return operations;
    }

    virtual void reset() {
        operations.clear();
    }

    virtual bool parse(const vector<gCode::Block> &blocks) = 0;
};

#endif //GRBL_MACHINE_H
