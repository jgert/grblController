//
// Created by Jakub Gert on 12/06/2020.
//

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "tests/TestSuite.h"
#include "SettingCodes.h"

class SettingCodesTests: TestSuite {
    Q_OBJECT

private slots:
    void testLoadingFile() {
        SettingCodes code(":csv/setting_codes_en_US.csv");

    }
};

static SettingCodesTests T_SettingCodeTests;
#include "SettingCodes.test.moc"
