//
// Created by Jakub Gert on 24/10/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "src/gCode/Parser.h"
#include "Engraver3axis.h"

using namespace gCode;

class Engraver3axisG20Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG20(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidArgumentsCount));
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG20(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G21");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG20(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G20.1");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG20(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidCommandNumber));
    }

    void testSwitchToImperial() {
        auto parser = gCode::Parser();
        parser.parse("G20");
        State state;
        state.units = State::Metric;
        Engraver3axis engraver(state);
        auto block = parser.blocks()[0];
        auto result = engraver.parseG20(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, true);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 0);
        QCOMPARE(engraver.getState().units, State::Imperial);
        QCOMPARE(engraver.getState().lastGCodeCommand, 20);
        QCOMPARE(engraver.getState().lastGCodeSubcommand, 0);
    }
};

static Engraver3axisG20Tests T_Engraver3axisG20Tests;

#include "Engraver3axis.G20.test.moc"
