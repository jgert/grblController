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
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 0);
    }

    void testPercent() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("%"), true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
    }

    void testLineNumber() {
        gCode::Parser parser;
        auto result = parser.parse("N10");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
        QCOMPARE(parser.blocks()[0].chunks[0].hasProgramLineNumber, true);
        QCOMPARE(parser.blocks()[0].chunks[0].programLineNumber, 10);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::LineNumber);
    }

    void testLineNumberWithCodeWithSpace() {
        gCode::Parser parser;
        auto result = parser.parse("N10 G20");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 2);
        QCOMPARE(parser.blocks()[0].chunks[1].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[0].startPosition, 0);
        QCOMPARE(parser.blocks()[0].chunks[1].startPosition, 4);
    }

    void testLineNumberWithCodeWithoutSpace() {
        gCode::Parser parser;
        auto result = parser.parse("n10G20");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 2);
        QCOMPARE(parser.blocks()[0].chunks[1].startPosition, 3);
    }

    void testInvalidGcode() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("G"), false);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::Error);
        QCOMPARE(parser.blocks()[0].chunks[0].comment, "G");
        QCOMPARE(parser.blocks()[0].chunks[0].startPosition, 0);
    }

    void testG1() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("g1"), true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[0].hasProgramLineNumber, false);
        QCOMPARE(parser.blocks()[0].chunks[0].hasSubcommand, false);
        QCOMPARE(parser.blocks()[0].chunks[0].startPosition, 0);
    }

    void testT10() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("T10"), true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::Tool);
        QCOMPARE(parser.blocks()[0].chunks[0].command, 10);
    }

    void testG01() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("g01"), true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
    }

    void testG38_3() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("g38.3"), true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
        gCode::Chunk chunk = parser.blocks()[0].chunks[0];
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
        QCOMPARE(parser.parse("X -7."), true);
        QCOMPARE(parser.blocks().size(), 7);
        QCOMPARE(parser.blocks()[0].chunks.size(), 1);
        QCOMPARE(parser.blocks()[0].chunks[0].address, 'X');
        QCOMPARE(parser.blocks()[0].chunks[0].value, -1.0);
        QCOMPARE(parser.blocks()[1].chunks.size(), 1);
        QCOMPARE(parser.blocks()[1].chunks[0].address, 'X');
        QCOMPARE(parser.blocks()[1].chunks[0].value, -2.0);
        QCOMPARE(parser.blocks()[2].chunks.size(), 1);
        QCOMPARE(parser.blocks()[2].chunks[0].address, 'X');
        QCOMPARE(parser.blocks()[2].chunks[0].value, 3.0);
        QCOMPARE(parser.blocks()[3].chunks.size(), 1);
        QCOMPARE(parser.blocks()[3].chunks[0].address, 'X');
        QCOMPARE(parser.blocks()[3].chunks[0].value, 4.0);
        QCOMPARE(parser.blocks()[4].chunks.size(), 1);
        QCOMPARE(parser.blocks()[4].chunks[0].address, 'X');
        QCOMPARE(parser.blocks()[4].chunks[0].value, 5.0);
        QCOMPARE(parser.blocks()[5].chunks.size(), 1);
        QCOMPARE(parser.blocks()[5].chunks[0].address, 'X');
        QCOMPARE(parser.blocks()[5].chunks[0].value, -6.0);
        QCOMPARE(parser.blocks()[5].chunks.size(), 1);
        QCOMPARE(parser.blocks()[6].chunks[0].address, 'X');
        QCOMPARE(parser.blocks()[6].chunks[0].value, -7.0);
    }

    void testInvalid() {
        gCode::Parser parser;
        QCOMPARE(parser.parse("G10 \\10"), false);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 2);
        QCOMPARE(parser.blocks()[0].chunks[1].type, gCode::Chunk::Error);
        QCOMPARE(parser.blocks()[0].chunks[1].comment, "\\10");
        QCOMPARE(parser.blocks()[0].chunks[1].startPosition, 4);
    }

    void testMultiline() {
        gCode::Parser parser;
        auto result = parser.parse("G10\nG20");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 2);
        QCOMPARE(parser.blocks()[0].chunks[0].startPosition, 0);
        QCOMPARE(parser.blocks()[1].chunks[0].startPosition, 0);
    }

    void testComment1() {
        gCode::Parser parser;
        auto result = parser.parse("G20 ; comment G30");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 2);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[0].command, 20);
        QCOMPARE(parser.blocks()[0].chunks[1].type, gCode::Chunk::Comment);
        QCOMPARE(parser.blocks()[0].chunks[1].type, gCode::Chunk::Comment);
        QCOMPARE(parser.blocks()[0].chunks[1].comment, "; comment G30");
    }

    void testCommentInline1() {
        gCode::Parser parser;
        auto result = parser.parse("G10 (G2 comment G01) G11");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 3);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[0].command, 10);
        QCOMPARE(parser.blocks()[0].chunks[1].type, gCode::Chunk::Comment);
        QCOMPARE(parser.blocks()[0].chunks[1].comment, "(G2 comment G01)");
        QCOMPARE(parser.blocks()[0].chunks[2].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[2].command, 11);
    }

    void testCommentInline2() {
        gCode::Parser parser;
        auto result = parser.parse("G10 [G2 comment G01] G11");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 3);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[0].command, 10);
        QCOMPARE(parser.blocks()[0].chunks[1].type, gCode::Chunk::Comment);
        QCOMPARE(parser.blocks()[0].chunks[1].comment, "[G2 comment G01]");
        QCOMPARE(parser.blocks()[0].chunks[2].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[2].command, 11);
    }

    void testBlock() {
        gCode::Parser parser;
        auto result = parser.parse("G01X20 Y30 Z-30\n\nG02X30");
        QCOMPARE(result, true);
        QCOMPARE(parser.blocks().size(), 3);
        QCOMPARE(parser.blocks()[0].chunks.size(), 4);
        QCOMPARE(parser.blocks()[1].chunks.size(), 0);
        QCOMPARE(parser.blocks()[2].chunks.size(), 2);
    }

    void testPosition() {
        gCode::Parser parser;
        auto result = parser.parse("G01X20 Y30 Z-30 foo");
        QCOMPARE(result, false);
        QCOMPARE(parser.blocks().size(), 1);
        QCOMPARE(parser.blocks()[0].chunks.size(), 5);

        // G01
        QCOMPARE(parser.blocks()[0].chunks[0].startPosition, 0);
        QCOMPARE(parser.blocks()[0].chunks[0].type, gCode::Chunk::Command);
        QCOMPARE(parser.blocks()[0].chunks[0].command, 1);

        // X20
        QCOMPARE(parser.blocks()[0].chunks[1].startPosition, 3);
        QCOMPARE(parser.blocks()[0].chunks[1].type, gCode::Chunk::Address);
        QCOMPARE(parser.blocks()[0].chunks[1].address, 'X');
        QCOMPARE(parser.blocks()[0].chunks[1].value, 20);

        // Y30
        QCOMPARE(parser.blocks()[0].chunks[2].startPosition, 7);
        QCOMPARE(parser.blocks()[0].chunks[2].type, gCode::Chunk::Address);
        QCOMPARE(parser.blocks()[0].chunks[2].address, 'Y');
        QCOMPARE(parser.blocks()[0].chunks[2].value, 30);

        // Z-30
        QCOMPARE(parser.blocks()[0].chunks[3].startPosition, 11);
        QCOMPARE(parser.blocks()[0].chunks[3].type, gCode::Chunk::Address);
        QCOMPARE(parser.blocks()[0].chunks[3].address, 'Z');
        QCOMPARE(parser.blocks()[0].chunks[3].value, -30);


        QCOMPARE(parser.blocks()[0].chunks[4].startPosition, 16);
        QCOMPARE(parser.blocks()[0].chunks[4].type, gCode::Chunk::Error);
        QCOMPARE(parser.blocks()[0].chunks[4].comment, "foo");
        QCOMPARE(parser.blocks()[0].chunks[4].startPosition, 16);
    }
};

static ParserTests T_ParserTests;

#include "Parser.test.moc"
