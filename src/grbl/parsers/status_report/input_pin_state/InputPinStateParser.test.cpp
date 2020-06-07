//
// Created by Jakub Gert on 07/06/2020.
//

#include <QObject>
#include <QtTest>
#include "tests/TestSuite.h"
#include "InputPinStateParser.h"

class InputPinStateTest : public TestSuite {
Q_OBJECT

private slots:

    void testInvalid() {
        InputPinStateParser parser;

        bool result = parser.parse("P:X");
        QCOMPARE(result, false);
    }

    void testXYZPDHRS() {
        InputPinStateParser parser;

        bool result = parser.parse("Pn:XYZPDHRS");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.xLimit = true;
        expected.yLimit = true;
        expected.zLimit = true;
        expected.probe = true;
        expected.door = true;
        expected.hold = true;
        expected.softReset = true;
        expected.cycleStart = true;

        QCOMPARE(state, expected);
    }

    void testX() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:X");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.xLimit = true;

        QCOMPARE(state, expected);
    }

    void testY() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:Y");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.yLimit = true;

        QCOMPARE(state, expected);
    }

    void testZ() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:Z");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.zLimit = true;

        QCOMPARE(state, expected);
    }

    void testP() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:P");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.probe = true;

        QCOMPARE(state, expected);
    }

    void testD() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:D");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.door = true;

        QCOMPARE(state, expected);
    }

    void testH() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:H");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.hold = true;

        QCOMPARE(state, expected);
    }

    void testR() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:R");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.softReset = true;

        QCOMPARE(state, expected);
    }

    void testS() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:S");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.cycleStart = true;

        QCOMPARE(state, expected);
    }

    void testRDX() {
        InputPinStateParser parser;
        bool result = parser.parse("Pn:RDX");
        QCOMPARE(result, true);

        auto state = parser.getInputPinState();

        InputPinState expected;
        expected.softReset = true;
        expected.xLimit = true;
        expected.door = true;

        QCOMPARE(state, expected);
    }
};

static InputPinStateTest T_InputPinStateTest;

#include "InputPinStateParser.test.moc"
