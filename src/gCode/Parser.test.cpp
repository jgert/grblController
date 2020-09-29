#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "tests/TestSuite.h"
#include "src/gCode/Parser.h"

class ParserTests : public TestSuite {
Q_OBJECT

private slots:

    void testEmpty() {
        gCode::Parser parser;
        QCOMPARE(parser.parse(""), true);
        QCOMPARE(parser.chunks().size(), 0);
    }

    void testPercent() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("%"), true);
        QCOMPARE(parser.chunks().size(), 1);
    }

    void testLineNumber() {
        gCode::Parser parser;
        auto result = parser.parse("N10");
        QCOMPARE(result, true);
        QCOMPARE(parser.chunks().size(), 1);
        QCOMPARE(parser.chunks()[0].hasLineNumber, true);
        QCOMPARE(parser.chunks()[0].lineNumber, 10);
        QCOMPARE(parser.chunks()[0].type, gCode::Chunk::LineNumber);
    }

    void testLineNumberWithCodeWithSpace() {
        gCode::Parser parser;
        auto result = parser.parse("N10 G20");
        QCOMPARE(result, true);
        QCOMPARE(parser.chunks().size(), 2);
        QCOMPARE(parser.chunks()[1].type, gCode::Chunk::Command);
    }

    void testLineNumberWithCodeWithoutSpace() {
        gCode::Parser parser;
        auto result = parser.parse("n10G20");
        QCOMPARE(result, true);
        QCOMPARE(parser.chunks().size(), 2);
    }

    void testInvalidGcode() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("G"), false);
        QCOMPARE(parser.chunks().size(), 0);
    }

    void testG1() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("g1"), true);
        QCOMPARE(parser.chunks().size(), 1);
        QCOMPARE(parser.chunks()[0].type, gCode::Chunk::Command);
        QCOMPARE(parser.chunks()[0].hasLineNumber, false);
        QCOMPARE(parser.chunks()[0].hasSubcommand, false);
    }

    void testT10() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("T10"), true);
        QCOMPARE(parser.chunks().size(), 1);
        QCOMPARE(parser.chunks()[0].type, gCode::Chunk::Tool);
        QCOMPARE(parser.chunks()[0].command, 10);
    }

    void testG01() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("g01"), true);
        QCOMPARE(parser.chunks().size(), 1);
    }

    void testG38_3() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("g38.3"), true);
        QCOMPARE(parser.chunks().size(), 1);
        gCode::Chunk chunk = parser.chunks()[0];
        QCOMPARE(chunk.type, gCode::Chunk::Command);
        QCOMPARE(chunk.command, 38);
        QCOMPARE(chunk.hasSubcommand, true);
        QCOMPARE(chunk.subcommand, 3);
    }

    void testX() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("X-1"), true);
        QCOMPARE(parser.parse("X-2.0"), true);
        QCOMPARE(parser.parse("X+3.0"), true);
        QCOMPARE(parser.parse("X +4.0"), true);
        QCOMPARE(parser.parse("X +5.0"), true);
        QCOMPARE(parser.parse("X -6.0"), true);
        QCOMPARE(parser.chunks().size(), 6);
    }
};

static ParserTests T_ParserTests;

#include "Parser.test.moc"
