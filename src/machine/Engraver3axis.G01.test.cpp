//
// Created by Jakub Gert on 23/10/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "src/gCode/Parser.h"
#include "Engraver3axis.h"

using namespace gCode;

class Engraver3axisG01Tests : public TestSuite {
Q_OBJECT
private slots:

    void testMissingArgument() {
        auto parser = gCode::Parser();
        parser.parse("");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG01(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::MissingArguments));
    }

    void testInvalidCommandChunkType() {
        auto parser = gCode::Parser();
        parser.parse("X10");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG01(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidCommandChunkType));
    }

    void testInvalidCommandNumber() {
        auto parser = gCode::Parser();
        parser.parse("G00");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG01(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidCommandNumber));
    }

    void testUnexpectedSubcommand() {
        auto parser = gCode::Parser();
        parser.parse("G01.1");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG01(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidCommandNumber));
    }

    void testInvalidUnexpectedChunkType() {
        auto parser = gCode::Parser();
        parser.parse("G01 N10");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG01(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::UnexpectedChunkType));
    }

    void testInvalidAddress() {
        auto parser = gCode::Parser();
        parser.parse("G01 P1");
        Engraver3axis engraver;
        auto block = parser.blocks()[0];
        auto result = engraver.parseG01(block);
        auto operations = engraver.getOperations();
        auto errors = engraver.getErrors();
        QCOMPARE(result, false);
        QCOMPARE(operations.size(), 0);
        QCOMPARE(errors.size(), 1);
        QCOMPARE(errors[0], Error(0, Error::InvalidAddress));
    }

    void testMetricSystemAbsolute() {
        auto state = State();
        state.units = State::Metric;
        state.currentPosition = QVector3D(1, 2, 3);
        state.coordinateMode = State::Absolute;
        auto parser = gCode::Parser();
        parser.parse("G01 X2");
        Engraver3axis engraver(state);
        const auto block = parser.blocks()[0];
        const auto result = engraver.parseG01(block);
        auto &operations = engraver.getOperations();
        auto &errors = engraver.getErrors();
        QCOMPARE(result, true);
        QCOMPARE(operations.size(), 1);
        QCOMPARE(errors.size(), 0);
        QCOMPARE(engraver.getState().lastGCodeCommand, 1);
        QCOMPARE(engraver.getState().lastGCodeSubcommand, 0);
        auto operation = operations[0];
        QCOMPARE(operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(2, 2, 3), -1)));
    }

    void testImperialSystemAbsolute() {
        auto state = State();
        state.units = State::Imperial;
        state.currentPosition = QVector3D(1, 2, 3);
        state.coordinateMode = State::Absolute;
        auto parser = gCode::Parser();
        parser.parse("G01 X2");
        Engraver3axis engraver(state);
        const auto block = parser.blocks()[0];
        const auto result = engraver.parseG01(block);
        auto &operations = engraver.getOperations();
        auto &errors = engraver.getErrors();
        QCOMPARE(result, true);
        QCOMPARE(operations.size(), 1);
        QCOMPARE(errors.size(), 0);
        QCOMPARE(engraver.getState().lastGCodeCommand, 1);
        QCOMPARE(engraver.getState().lastGCodeSubcommand, 0);
        auto operation = operations[0];
        QCOMPARE(operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(50.8, 2, 3), -1)));
    }

    void testMetricSystemIncremental() {
        auto state = State();
        state.units = State::Metric;
        state.currentPosition = QVector3D(1, 2, 3);
        state.coordinateMode = State::Incremental;
        auto parser = gCode::Parser();
        parser.parse("G01 Y2");
        Engraver3axis engraver(state);
        const auto block = parser.blocks()[0];
        const auto result = engraver.parseG01(block);
        auto &operations = engraver.getOperations();
        auto &errors = engraver.getErrors();
        QCOMPARE(result, true);
        QCOMPARE(operations.size(), 1);
        QCOMPARE(errors.size(), 0);
        QCOMPARE(engraver.getState().lastGCodeCommand, 1);
        QCOMPARE(engraver.getState().lastGCodeSubcommand, 0);
        auto operation = operations[0];
        QCOMPARE(operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(1, 4, 3), -1)));
    }

    void testImperialSystemIncremental() {
        auto state = State();
        state.units = State::Imperial;
        state.currentPosition = QVector3D(1, 2, 3);
        state.coordinateMode = State::Incremental;
        auto parser = gCode::Parser();
        parser.parse("G01 Z2");
        Engraver3axis engraver(state);
        const auto block = parser.blocks()[0];
        const auto result = engraver.parseG01(block);
        auto &operations = engraver.getOperations();
        auto &errors = engraver.getErrors();
        QCOMPARE(result, true);
        QCOMPARE(operations.size(), 1);
        QCOMPARE(errors.size(), 0);
        QCOMPARE(engraver.getState().lastGCodeCommand, 1);
        QCOMPARE(engraver.getState().lastGCodeSubcommand, 0);
        auto operation = operations[0];
        QCOMPARE(operation, Operation(OperationMove(QVector3D(1, 2, 3), QVector3D(1, 2, 53.8), -1)));
    }
};

static Engraver3axisG01Tests T_Engraver3axisG01Tests;

#include "Engraver3axis.G01.test.moc"
