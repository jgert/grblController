//
// Created by Jakub Gert on 04/05/2021.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "Parser.h"

using namespace gCode;
using namespace machine;

class G19Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G19(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidArgumentsCount));
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G19(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G21");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G19(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G20.1");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G19(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testSwitchToYZ() {
        auto parser = gCode::Parser();
        parser.parse("G19");
        auto block = parser.blocks()[0];
        MachineState nextState;
        nextState.planeSelection = MachineState::PlaneSelection::XY;
        auto result = G19(block, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.planeSelection, MachineState::YZ);
        QCOMPARE(nextState.lastGCodeCommand, 19);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
    }
};

static G19Tests T_G19Tests;

#include "G19.test.moc"
