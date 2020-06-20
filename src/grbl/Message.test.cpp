//
// Created by Jakub Gert on 20/06/2020.
//

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "tests/TestSuite.h"
#include "src/grbl/Message.h"

class MessageTests : public TestSuite {
Q_OBJECT

private slots:

    void testCustom() {
        auto message = Message::custom("ABC");
        QCOMPARE(message.data, "ABC");
    }

    void testMessageInfo() {
        auto message = Message::messageInfo();
        QCOMPARE(message.data, "$I\n");
    }

    void testMessageKillAlarm() {
        auto message = Message::messageKillAlarm();
        QCOMPARE(message.data, "$X\n");
    }

    void testMessageSetSetting() {
        auto settingItem = SettingItem();
        settingItem.code = 20;
        settingItem.value = "abc";
        auto message = Message::messageSetSetting(settingItem);
        QCOMPARE(message.data, "$20=abc\n");
    }

    void testMessageSettings() {
        auto message = Message::messageSettings();
        QCOMPARE(message.data, "$$\n");
    }
};

static MessageTests T_Message;

#include "Message.test.moc"
