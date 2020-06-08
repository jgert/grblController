//
// Created by Jakub Gert on 03/06/2020.
//

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "tests/TestSuite.h"
#include "src/grbl/GRBL.h"

Q_DECLARE_METATYPE(State)

Q_DECLARE_METATYPE(MachineState)

Q_DECLARE_METATYPE(vec3)

class GRBLTests : public TestSuite {
Q_OBJECT

private slots:

    void initTestCase() {
        qRegisterMetaType<State>();
        qRegisterMetaType<MachineState>();
        qRegisterMetaType<vec3>();
    }

    void testIntegrationMachineStateValid() {
        GRBL controller;

        QSignalSpy spy(&controller, &GRBL::onReceivedMachineState);

        controller.parse("<Door:1>");

        QCOMPARE(spy.count(), 1);
        MachineState state = qvariant_cast<MachineState>(spy.takeFirst()[0]);
        QCOMPARE(state.state, State::Door);
        QCOMPARE(state.code, 1);
    }

    void testIntegrationMachineStateInvalid() {
        GRBL controller;

        QSignalSpy spy(&controller, &GRBL::onReceivedMachineState);

        controller.parse("<FooState>");

        QCOMPARE(spy.count(), 0);
    }

    void testIntegrationMachineStatePositionWPos() {
        GRBL controller;

        QSignalSpy spyMPos(&controller, &GRBL::onReceivedMPos);
        QSignalSpy spyWPos(&controller, &GRBL::onReceivedWPos);

        controller.parse("<MPos:10,20,30|WCO:50.000,60.00,70.00>");

        QCOMPARE(spyMPos.count(), 2);
        QCOMPARE(spyWPos.count(), 2);

        QCOMPARE(qvariant_cast<vec3>(spyMPos[0].takeFirst()), vec3(10, 20, 30));
        QCOMPARE(qvariant_cast<vec3>(spyWPos[0].takeFirst()), vec3(10, 20, 30));

        QCOMPARE(qvariant_cast<vec3>(spyMPos[1].takeFirst()), vec3(10, 20, 30));
        QCOMPARE(qvariant_cast<vec3>(spyWPos[1].takeFirst()), vec3(-40, -40, -40));
    }

    void testIntegrationMachineStatePositionMPos() {
        GRBL controller;

        QSignalSpy spyMPos(&controller, &GRBL::onReceivedMPos);
        QSignalSpy spyWPos(&controller, &GRBL::onReceivedWPos);

        controller.parse("<WPos:10,20,30|WCO:50.000,60.00,70.00>");

        QCOMPARE(spyMPos.count(), 2);
        QCOMPARE(spyWPos.count(), 2);

        QCOMPARE(qvariant_cast<vec3>(spyMPos[0].takeFirst()), vec3(10, 20, 30));
        QCOMPARE(qvariant_cast<vec3>(spyWPos[0].takeFirst()), vec3(10, 20, 30));

        QCOMPARE(qvariant_cast<vec3>(spyMPos[1].takeFirst()), vec3(60, 80, 100));
        QCOMPARE(qvariant_cast<vec3>(spyWPos[1].takeFirst()), vec3(10, 20, 30));
    }

};

//void GRBLTests::testParser() {
//    GRBL controller;
//
//    QSignalSpy spy(&controller, &GRBL::onReceiveMPos);
//
//    auto test = QString("<Idle|MPos:35.000,-105.000,95.000|FS:0,0|WCO:30.000,-100.000,-10.000>");
//    // 5. -5, 105
//    // 35, 105, 95
//    // <Idle|MPos:35.000,-105.000,95.000|FS:0,0|Ov:173,100,100>
//
////        auto test = QString("<MPos:10.23,-0.000,0.000>");
//    controller.parse(test);
//
//    QCOMPARE(spy.count(), 1);
//    QList<QVariant> result = spy.takeFirst();
//    QCOMPARE(result.at(0).toString(), "10.23");
//    QCOMPARE(result.at(1).toString(), "-0.000");
//    QCOMPARE(result.at(2).toString(), "0.000");
//}

static GRBLTests T_GRBLTests;


#include "GRBL.test.moc"
