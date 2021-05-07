//
// Created by Jakub Gert on 04/05/2021.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "Parser.h"

using namespace gCode;
using namespace machine;

class G18Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G18(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.error, Error(0, Error::InvalidArgumentsCount));
        QCOMPARE(nextState.operation, Operation());
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G18(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G21");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G18(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G20.1");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G18(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testSwitchToYZ() {
        auto parser = gCode::Parser();
        parser.parse("G18");
        MachineState nextState;
        nextState.planeSelection = MachineState::PlaneSelection::XY;
        auto block = parser.blocks()[0];
        auto result = G18(block, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.planeSelection, MachineState::ZX);
        QCOMPARE(nextState.lastGCodeCommand, 18);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
    }
};

static G18Tests T_G18Tests;

#include "G18.test.moc"
