//
// Created by Jakub Gert on 23/10/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "Parser.h"

using namespace gCode;
using namespace machine;

class G01Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        auto block = parser.blocks()[0];
        const auto currentState = MachineState();
        auto nextState = currentState;
        auto result = G01(block, currentState, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::MissingArguments));
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        auto block = parser.blocks()[0];
        const auto currentState = MachineState();
        auto nextState = currentState;
        auto result = G01(block, currentState, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G00");
        auto block = parser.blocks()[0];
        const auto currentState = MachineState();
        auto nextState = currentState;
        auto result = G01(block, currentState, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G01.1");
        auto block = parser.blocks()[0];
        const auto currentState = MachineState();
        auto nextState = currentState;
        auto result = G01(block, currentState, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testInvalidUnexpectedChunkType() {
        auto parser = gCode::Parser();
        parser.parse("G01 N10");
        auto block = parser.blocks()[0];
        const auto currentState = MachineState();
        auto nextState = currentState;
        auto result = G01(block, currentState, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::UnexpectedChunkType));
    }

    void testInvalidAddress() {
        auto parser = gCode::Parser();
        parser.parse("G01 P1");
        auto block = parser.blocks()[0];
        const auto currentState = MachineState();
        auto nextState = currentState;
        auto result = G01(block, currentState, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidAddress));
    }

    void testMetricSystemAbsolute() {
        auto parser = gCode::Parser();
        parser.parse("G01 X2");
        const auto block = parser.blocks()[0];
        auto initialState = MachineState();
        initialState.units = MachineState::Metric;
        initialState.currentPosition = QVector3D(1, 2, 3);
        initialState.coordinateMode = MachineState::Absolute;
        const auto currentState = initialState;
        auto nextState = currentState;
        const auto result = G01(block, currentState, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.lastGCodeCommand, 1);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
        QCOMPARE(nextState.operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(2, 2, 3), -1)));
    }

    void testImperialSystemAbsolute() {
        auto parser = gCode::Parser();
        parser.parse("G01 X2");
        const auto block = parser.blocks()[0];
        auto initialState = MachineState();
        initialState.units = MachineState::Imperial;
        initialState.currentPosition = QVector3D(1, 2, 3);
        initialState.coordinateMode = MachineState::Absolute;
        const auto currentState = initialState;
        auto nextState = currentState;
        const auto result = G01(block, currentState, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.lastGCodeCommand, 1);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
        QCOMPARE(nextState.operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(50.8, 2, 3), -1)));
    }

    void testMetricSystemIncremental() {
        auto parser = gCode::Parser();
        parser.parse("G01 Y2");
        const auto block = parser.blocks()[0];
        auto initialState = MachineState();
        initialState.units = MachineState::Metric;
        initialState.currentPosition = QVector3D(1, 2, 3);
        initialState.coordinateMode = MachineState::Incremental;
        const auto currentState = initialState;
        auto nextState = currentState;
        const auto result = G01(block, currentState, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.lastGCodeCommand, 1);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
        QCOMPARE(nextState.operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(1, 4, 3), -1)));
    }

    void testImperialSystemIncremental() {
        auto parser = gCode::Parser();
        parser.parse("G01 Z2");
        const auto block = parser.blocks()[0];
        auto initialState = MachineState();
        initialState.units = MachineState::Imperial;
        initialState.currentPosition = QVector3D(1, 2, 3);
        initialState.coordinateMode = MachineState::Incremental;
        const auto currentState = initialState;
        auto nextState = currentState;
        const auto result = G01(block, currentState, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.lastGCodeCommand, 1);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
        QCOMPARE(nextState.operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(1, 2, 53.8), -1)));
    }
};

static G01Tests T_G01Tests;

#include "G01.test.moc"
