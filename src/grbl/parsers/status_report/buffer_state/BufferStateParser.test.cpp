//
// Created by Jakub Gert on 06/06/2020.
//

#include <QObject>
#include <QTest>
#include "tests/TestSuite.h"
#include "BufferStateParser.h"

class BufferStateParserTests : public TestSuite {
Q_OBJECT

private slots:

    void testValid() {
        BufferStateParser parser;

        bool result = parser.parse("Bf:10,220");

        QCOMPARE(result,true);

        BufferState state = parser.getBufferState();
        QCOMPARE(state.availableBlocks, 10);
        QCOMPARE(state.availableBytesInRxBuffer, 220);
    }

    void testInvalid() {
        BufferStateParser parser;

        bool result;

        result = parser.parse("bf:10,220");

        QCOMPARE(result,false);

        result = parser.parse("Bf:10,");
        QCOMPARE(result, false);
    }
};

static BufferStateParserTests T_BufferStateParserTests;

#include "BufferStateParser.test.moc"