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

    explicit Operation(OperationMove move) : type(Move), operationMove(move) {}
};

inline bool operator==(const OperationMove &lhs, const OperationMove &rhs) {
    return (lhs.from == rhs.from) && (lhs.to == rhs.to) && (lhs.speed == rhs.speed);
};

inline bool operator==(const Operation &lhs, const Operation &rhs) {
    return lhs.type == rhs.type && lhs.operationMove == rhs.operationMove;
};

typedef struct Error {
    typedef enum {
        NotSupported,
        InvalidCommandChunkType,
        InvalidCommandNumber,
        UnexpectedChunkType,
        InvalidAddress,
        MissingArguments,
        InvalidArgumentsCount,
    } Error_t;

    uint32_t lineNumber;
    Error_t type;

    Error(uint32_t lineNumber, Error_t type) : lineNumber(lineNumber), type(type) {

    }

    [[nodiscard]] string description() const {
        return to_string(lineNumber) + ":" + typeDescription(type);
    }

    [[nodiscard]] static string typeDescription(Error_t error) {
        switch (error) {
            case NotSupported:
                return "not supported";
            case InvalidCommandChunkType:
                return "invalid command chunk type";
            case InvalidCommandNumber:
                return "invalid command number";
            case UnexpectedChunkType:
                return "unexpected chunk type";
            case InvalidAddress:
                return "invalid address";
            case MissingArguments:
                return "missing arguments";
            case InvalidArgumentsCount:
                return "invalid arguments count";
        }
    }

} Error_t;

inline bool operator==(const Error &lhs, const Error &rhs) {

    return lhs.lineNumber == rhs.lineNumber &&
           lhs.type == rhs.type;
}

class Machine {
protected:
    vector<Operation> operations;
    vector<Error> errors;
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

    [[nodiscard]] const vector<Error> &getErrors() const;

    virtual bool parse(const vector<gCode::Block> &blocks) = 0;
};

#endif //GRBL_MACHINE_H
