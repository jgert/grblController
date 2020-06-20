//
// Created by Jakub Gert on 20/06/2020.
//

#include <QObject>
#include <QTest>
#include "tests/TestSuite.h"
#include "ResponseMessageParser.h"

class ResponseMessageParserTests : public TestSuite {
Q_OBJECT
private slots:

    void testInvalid() {
        ResponseMessageParser parser;

        auto result = parser.parse("o");
        QCOMPARE(result, false);

        result = parser.parse("error");
        QCOMPARE(result, false);

        result = parser.parse("error:");
        QCOMPARE(result, false);

        result = parser.parse("error:a");
        QCOMPARE(result, false);
    }

    void testValid() {
        ResponseMessageParser parser;

        auto result = parser.parse("ok");
        QCOMPARE(result, true);
        QCOMPARE(parser.getError(), 0);

        result = parser.parse("error:0");
        QCOMPARE(result, true);
        QCOMPARE(parser.getError(), 0);
    }
};

static ResponseMessageParserTests T_ResponseMessageParserTests;

#include "ResponseMessageParser.test.moc"
