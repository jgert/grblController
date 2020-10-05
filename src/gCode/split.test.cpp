#include <tests/TestSuite.h>
#include <qtestcase.h>
#include "split.h"

using namespace std;

class SplitTests : public TestSuite {
Q_OBJECT

private slots:

    void testSplit() {
        auto text = string("test");
        auto result = gCode::splitByNewLine(text);

        QCOMPARE(result.size(), 1);
        QCOMPARE(result[0], "test");

        text = string("line0\nline1");
        result = gCode::splitByNewLine(text);
        QCOMPARE(result.size(), 2);
        QCOMPARE(result[0], "line0");
        QCOMPARE(result[1], "line1");

        text = string("\nline1\n\n\nline_4\n\n");
        result = gCode::splitByNewLine(text);
        QCOMPARE(result.size(), 6);
        QCOMPARE(result[0], "");
        QCOMPARE(result[1], "line1");
        QCOMPARE(result[2], "");
        QCOMPARE(result[3], "");
        QCOMPARE(result[4], "line_4");
        QCOMPARE(result[5], "");
    }

    void testSplitCRLF() {
        auto text = string("test");
        auto result = gCode::splitByNewLine(text);

        QCOMPARE(result.size(), 1);
        QCOMPARE(result[0], "test");

        text = string("line0\r\nline1");
        result = gCode::splitByNewLine(text);
        QCOMPARE(result.size(), 2);
        QCOMPARE(result[0], "line0");
        QCOMPARE(result[1], "line1");

        text = string("\r\nline1\r\n\r\n\r\nline_4\r\n\r\n");
        result = gCode::splitByNewLine(text);
        QCOMPARE(result.size(), 6);
        QCOMPARE(result[0], "");
        QCOMPARE(result[1], "line1");
        QCOMPARE(result[2], "");
        QCOMPARE(result[3], "");
        QCOMPARE(result[4], "line_4");
        QCOMPARE(result[5], "");
    }
};

static SplitTests T_SplitTests;

#include "split.test.moc"