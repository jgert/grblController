//
// Created by Jakub Gert on 07/06/2020.
//

#include <QObject>
#include <QTest>
#include "tests/TestSuite.h"
#include "AccessoryStateParser.h"

class AccessoryStateParserTests : public TestSuite {
Q_OBJECT
private slots:

    void testInvalid() {
        AccessoryStateParser parser;

        bool result = parser.parse("A:");

        QCOMPARE(result,false);
    }

    void testSpindleCW() {
        AccessoryStateParser parser;

        bool result = parser.parse("A:S");
        QCOMPARE(result,true);

        AccessoryState expected;
        expected.spindleState = AccessoryState::enabledCW;

        QCOMPARE(parser.getAccessoryState(), expected);
    }

    void testSpindleCCW() {
        AccessoryStateParser parser;

        bool result = parser.parse("A:C");
        QCOMPARE(result,true);

        AccessoryState expected;
        expected.spindleState = AccessoryState::enabledCCW;

        QCOMPARE(parser.getAccessoryState(), expected);
    }

    void testFloodCoolant() {
        AccessoryStateParser parser;

        bool result = parser.parse("A:F");
        QCOMPARE(result,true);

        AccessoryState expected;
        expected.floodCoolant = true;

        QCOMPARE(parser.getAccessoryState(), expected);
    }

    void testMistCoolant() {
        AccessoryStateParser parser;

        bool result = parser.parse("A:M");
        QCOMPARE(result,true);

        AccessoryState expected;
        expected.mistCoolant = true;

        QCOMPARE(parser.getAccessoryState(), expected);
    }
};

static AccessoryStateParserTests T_AccessoryStateParserTests;

#include "AccessoryStateParser.test.moc"
