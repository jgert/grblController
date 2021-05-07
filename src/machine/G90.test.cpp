//
// Created by Jakub Gert on 24/10/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "Parser.h"

using namespace gCode;
using namespace machine;

class G90Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G90(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidArgumentsCount));
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G90(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G20");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G90(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G90.1");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G90(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testSwitchToAbsolute() {
        auto parser = gCode::Parser();
        parser.parse("G90");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        nextState.coordinateMode = MachineState::Incremental;
        auto result = G90(block, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.coordinateMode, MachineState::Absolute);
        QCOMPARE(nextState.lastGCodeCommand, 90);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
    }
};

static G90Tests T_G90Tests;

#include "G90.test.moc"
