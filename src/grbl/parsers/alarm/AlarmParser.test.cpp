//
// Created by Jakub Gert on 10/06/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "AlarmParser.h"

class AlarmParserTests : public TestSuite {
Q_OBJECT
private slots:

    void testAlarm() {
        AlarmParser parser;

        bool result;

        result = parser.parse("ALARM:20");
        QCOMPARE(result, true);
        QCOMPARE(parser.getAlarmValue(), 20);

        result = parser.parse("ALARM:0");
        QCOMPARE(result, true);
        QCOMPARE(parser.getAlarmValue(), 0);
    }

    void testInvalidValues() {
        AlarmParser parser;

        bool result;

        result = parser.parse("ALARM:a");
        QCOMPARE(result, false);

        result = parser.parse("ALARM:-1");
        QCOMPARE(result, false);
    }
};

static AlarmParserTests T_AlarmParserTests;

#include "AlarmParser.test.moc"
