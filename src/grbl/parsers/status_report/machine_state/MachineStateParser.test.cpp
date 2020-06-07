//
// Created by Jakub Gert on 04/06/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "MachineStateParser.h"

class ParserMachineStateTests : public TestSuite {
Q_OBJECT

private slots:

    void testParseMachineStateUnknown() {
        MachineStateParser parser;

        bool result = parser.parse("Unknown");
        QCOMPARE(result, false);
    }

    void testParseMachineStateIdle() {
        MachineStateParser parser;

        bool result = parser.parse("Idle");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Idle);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateRun() {
        MachineStateParser parser;

        bool result = parser.parse("Run");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Run);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateHold() {
        MachineStateParser parser;

        bool result = parser.parse("Hold");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Hold);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateHold0() {
        MachineStateParser parser;

        bool result = parser.parse("Hold:0");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Hold);
        QCOMPARE(state.code, 0);
    }

    void testParseMachineStateHold1() {
        MachineStateParser parser;

        bool result = parser.parse("Hold:1");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Hold);
        QCOMPARE(state.code, 1);
    }

    void testParseMachineStateJog() {
        MachineStateParser parser;

        bool result = parser.parse("Jog");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Jog);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateAlarm() {
        MachineStateParser parser;

        bool result = parser.parse("Alarm");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Alarm);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateDoor() {
        MachineStateParser parser;

        bool result = parser.parse("Door");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Door);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateDoor0() {
        MachineStateParser parser;

        bool result = parser.parse("Door:0");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Door);
        QCOMPARE(state.code, 0);
    }

    void testParseMachineStateDoor1() {
        MachineStateParser parser;

        bool result = parser.parse("Door:1");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Door);
        QCOMPARE(state.code, 1);
    }

    void testParseMachineStateCheck() {
        MachineStateParser parser;

        bool result = parser.parse("Check");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Check);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateHome() {
        MachineStateParser parser;

        bool result = parser.parse("Home");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Home);
        QCOMPARE(state.code, -1);
    }

    void testParseMachineStateSleep() {
        MachineStateParser parser;

        bool result = parser.parse("Sleep");
        QCOMPARE(result, true);

        MachineState state = parser.getMachineState();

        QCOMPARE(state.state, State::Sleep);
        QCOMPARE(state.code, -1);
    }
};

static ParserMachineStateTests T_ParserMachineStateTests;

#include "MachineStateParser.test.moc"
