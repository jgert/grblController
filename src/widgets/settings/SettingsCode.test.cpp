//
// Created by Jakub Gert on 12/06/2020.
//

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "tests/TestSuite.h"
#include "SettingCodes.h"

class SettingsCodeTests: TestSuite {
    Q_OBJECT

private slots:
    void testLoadingFile() {
        SettingCodes code(":csv/setting_codes_en_US.csv");

    }
};

static SettingsCodeTests T_SettingsCodeTests;
#include "SettingsCode.test.moc"
