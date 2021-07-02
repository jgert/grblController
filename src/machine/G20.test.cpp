//
// Created by Jakub Gert on 24/10/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "Parser.h"

using namespace gCode;
using namespace machine;

class G20Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G20(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidArgumentsCount));
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G20(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G21");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G20(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G20.1");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G20(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testSwitchToImperial() {
        auto parser = gCode::Parser();
        parser.parse("G20");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        nextState.units = MachineState::Metric;
        auto result = G20(block, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.units, MachineState::Imperial);
        QCOMPARE(nextState.lastGCodeCommand, 20);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
    }
};

static G20Tests T_G20Tests;

#include "G20.test.moc"
