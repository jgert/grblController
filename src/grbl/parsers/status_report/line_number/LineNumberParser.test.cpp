//
// Created by Jakub Gert on 07/06/2020.
//

#include <QtTest/QtTest>
#include "tests/TestSuite.h"
#include "LineNumberParser.h"

class LineNumberParserTests : public TestSuite {
Q_OBJECT
private slots:

    void testLineNumber() {
        LineNumberParser parser;

        bool result = false;

        result = parser.parse("Ln:20");
        QCOMPARE(result, true);
        QCOMPARE(parser.getLineNumber(), 20);

        result = parser.parse("Ln:-20");
        QCOMPARE(result, true);
        QCOMPARE(parser.getLineNumber(), -20);
    }

    void testInvalidValues() {
        LineNumberParser parser;

        bool result = false;

        result = parser.parse("Ln:a");
        QCOMPARE(result, false);

        result = parser.parse("Ln:20.0");
        QCOMPARE(result, false);

        result = parser.parse("Ln:.0");
        QCOMPARE(result, false);

        result = parser.parse("L:20");
        QCOMPARE(result, false);
    }
};

static LineNumberParserTests T_LineNumberParserTests;

#include "LineNumberParser.test.moc"
