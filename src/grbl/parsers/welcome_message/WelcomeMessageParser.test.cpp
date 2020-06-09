//
// Created by Jakub Gert on 08/06/2020.
//

#include <QObject>
#include <QtTest>
#include "tests/TestSuite.h"
#include "WelcomeMessageParser.h"

class WelcomeMessageParserTest : public TestSuite {
Q_OBJECT
private slots:

    void testInvalid() {
        auto parser = WelcomeMessageParser();
        auto result = parser.parse("Grrbl 1 foo");
        QCOMPARE(result, false);

        result = parser.parse("Grbl 1 [foo]");
        QCOMPARE(result, false);

        result = parser.parse("Grbl 1. [foo]");
        QCOMPARE(result, false);

        result = parser.parse("GRBL 1. [foo]");
        QCOMPARE(result, false);
    }

    void testValid() {
        auto parser = WelcomeMessageParser();

        auto result = parser.parse("Grbl 1.0 [foo]");
        QCOMPARE(result, true);
        QCOMPARE(parser.getVersion(), "1.0");

        result = parser.parse("Grbl 1.0 ['$' for help]");
        QCOMPARE(result, true);
        QCOMPARE(parser.getVersion(), "1.0");

        result = parser.parse("Grbl 1.2a ['$' for help]");
        QCOMPARE(result, true);
        QCOMPARE(parser.getVersion(), "1.2a");
    }
};

static WelcomeMessageParserTest T_WelcomeMessageParserTest;

#include "WelcomeMessageParser.test.moc"
