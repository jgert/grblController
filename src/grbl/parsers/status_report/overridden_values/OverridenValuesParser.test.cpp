//
// Created by Jakub Gert on 07/06/2020.
//

#include <QObject>
#include <QtTest>
#include "tests/TestSuite.h"
#include "OverriddenValuesParser.h"

class OverriddenValuesParserTests : public TestSuite {
    Q_OBJECT

private slots:

    void testValid() {
        OverriddenValuesParser parser;
        bool result = parser.parse("Ov:10,20,30");
        QCOMPARE(result, true);
        OverriddenValues values = parser.getOverriddenValues();
        QCOMPARE(values.feed, 10);
        QCOMPARE(values.rapid, 20);
        QCOMPARE(values.spindle, 30);
    }

    void testInvalid() {
        OverriddenValuesParser parser;
        bool result = parser.parse("Ov:10,-20,30");
        QCOMPARE(result, false);
    }
};

static OverriddenValuesParserTests T_OverriddenValuesParserTests;

#include "OverridenValuesParser.test.moc"
