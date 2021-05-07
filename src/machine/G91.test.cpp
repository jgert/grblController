//
// Created by Jakub Gert on 24/10/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "Parser.h"

using namespace gCode;

class G91Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G91(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidArgumentsCount));
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G91(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G20");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G91(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G91.1");
        auto block = parser.blocks()[0];
        auto nextState = MachineState();
        auto result = G91(block, nextState);
        QCOMPARE(result, false);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error(0, Error::InvalidCommandNumber));
    }

    void testSwitchToIncremental() {
        auto parser = gCode::Parser();
        parser.parse("G91");
        auto nextState = MachineState();
        nextState.coordinateMode = MachineState::Absolute;
        auto block = parser.blocks()[0];
        auto result = G91(block, nextState);
        QCOMPARE(result, true);
        QCOMPARE(nextState.operation, Operation());
        QCOMPARE(nextState.error, Error());
        QCOMPARE(nextState.coordinateMode, MachineState::Incremental);
        QCOMPARE(nextState.lastGCodeCommand, 91);
        QCOMPARE(nextState.lastGCodeSubcommand, 0);
    }
};

static G91Tests T_G91Tests;

#include "G91.test.moc"
