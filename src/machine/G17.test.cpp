//
// Created by Jakub Gert on 04/05/2021.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "Parser.h"

class G17Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G17(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.error, Error(0, Error::InvalidArgumentsCount));
        QCOMPARE(nextState.operation, Operation());
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G17(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G21");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G17(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G20.1");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G17(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testSwitchToXY() {
        auto parser = gCode::Parser();
        parser.parse("G17");
        auto block = parser.blocks()[0];
        MachineState nextState;
        nextState.planeSelection = MachineState::PlaneSelection::YZ;
        auto result = G17(block, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.planeSelection, MachineState::XY);
        QCOMPARE(nextState.lastGCodeCommand, 17);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
    }
};

static G17Tests T_G17Tests;

#include "G17.test.moc"
