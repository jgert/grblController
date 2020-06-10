//
// Created by Jakub Gert on 10/06/2020.
//

#include <QObject>
#include <QTest>
#include "tests/TestSuite.h"
#include "ConfigurationParser.h"

class ConfigurationParserTests : public TestSuite {
Q_OBJECT
private slots:

    void testInvalid() {
        ConfigurationParser parser;

        bool result = parser.parse("$$=10");

        QCOMPARE(result, false);

        result = parser.parse("$:10");

        QCOMPARE(result, false);

        result = parser.parse("$=");

        QCOMPARE(result, false);

        result = parser.parse("$a:");

        QCOMPARE(result, false);
    }

    void testValid() {
        ConfigurationParser parser;

        bool result = parser.parse("$10=20");

        QCOMPARE(result, true);

        const ConfigurationItem item = parser.getConfigurationItem();

        QCOMPARE(item.code, 10);
        QCOMPARE(item.value, "20");
    }
};

static ConfigurationParserTests T_ConfigurationParserTests;

#include "ConfigurationParser.test.moc"
