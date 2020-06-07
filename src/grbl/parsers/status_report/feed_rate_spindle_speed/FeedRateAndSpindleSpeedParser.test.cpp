#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "FeedRateAndSpindleSpeedParser.h"

class FeedRateAndSpindleSpeedParserTests : public TestSuite {
Q_OBJECT
private slots:

    void testValidValues() {
        FeedRateAndSpindleSpeedParser parser;

        bool result;

        result = parser.parse("FS:20,30");
        QCOMPARE(result, true);
        QCOMPARE(parser.getFeedRate(), 20);
        QCOMPARE(parser.getSpindleSpeed(), 30);
    }

    void testInvalidValues() {
        FeedRateAndSpindleSpeedParser parser;

        bool result = false;

        result = parser.parse("FS:a");
        QCOMPARE(result, false);

        result = parser.parse("FS:20.0");
        QCOMPARE(result, false);

        result = parser.parse("FS:.0");
        QCOMPARE(result, false);

        result = parser.parse("FS:-20,20");
        QCOMPARE(result, false);

        result = parser.parse("FS:20,-20");
        QCOMPARE(result, false);
    }
};

static FeedRateAndSpindleSpeedParserTests T_FeedRateAndSpindleSpeedParserTests;

#include "FeedRateAndSpindleSpeedParser.test.moc"
