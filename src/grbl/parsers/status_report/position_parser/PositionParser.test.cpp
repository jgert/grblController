//
// Created by Jakub Gert on 07/06/2020.
//

#include <QObject>
#include <QtTest>
#include "tests/TestSuite.h"
#include "PositionParser.h"

class PositionParserTests : public TestSuite {
Q_OBJECT

private slots:

    void testValid() {
        PositionParser parser;
        bool result = parser.parse("MPos:-20.0,30.1,20.9");
        QCOMPARE(result, true);
        vec3 position = parser.getMachinePosition();
        QCOMPARE(position, vec3(-20, 30.1, 20.9));
    }

    void testInvalid() {
        PositionParser parser;
        bool result = parser.parse("Mpos:-20.0,30.1,20");
        QCOMPARE(result, false);
    }

    void testWPos() {
        PositionParser parser;
        bool result = parser.parse("WPos:-20.0,30.1,20.9");
        QCOMPARE(result, true);
        vec3 position = parser.getWorkPosition();
        QCOMPARE(position, vec3(-20, 30.1, 20.9));
    }

    void testWorkCoordinateOffset() {
        PositionParser parser;
        bool result = parser.parse("WCO:-20.0,30.1,20.9");
        QCOMPARE(result, true);
        vec3 position = parser.getWorkCoordinateOffset();
        QCOMPARE(position, vec3(-20, 30.1, 20.9));
    }
};

static PositionParserTests T_PositionParserTests;

#include "PositionParser.test.moc"
