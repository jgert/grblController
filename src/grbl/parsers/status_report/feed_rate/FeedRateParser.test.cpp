//
// Created by Jakub Gert on 07/06/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "FeedRateParser.h"

class FeedRateParserTests : public TestSuite {
Q_OBJECT
private slots:

    void testValidValues() {
        FeedRateParser parser;

        bool result;

        result = parser.parse("F:20");
        QCOMPARE(result, true);
        QCOMPARE(parser.getFeedRate(), 20);
    }

    void testInvalidValues() {
        FeedRateParser parser;

        bool result = false;

        result = parser.parse("F:a");
        QCOMPARE(result, false);

        result = parser.parse("F:20.0");
        QCOMPARE(result, false);

        result = parser.parse("F:.0");
        QCOMPARE(result, false);

        result = parser.parse("F:-20,20");
        QCOMPARE(result, false);

        result = parser.parse("a:20");
        QCOMPARE(result, false);
    }
};

static FeedRateParserTests T_FeedRateParserTests;

#include "FeedRateParser.test.moc"
