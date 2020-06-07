//
// Created by Jakub Gert on 07/06/2020.
//

#include <QApplication>
#include <QDebug>
#include <QStyle>
#include <QTest>
#include <QtTest/QtTest>
#include "src/MainWindow.h"
#include "src/grbl/GRBL.h"
#include "tests/TestSuite.h"
#include <regex>

using namespace std;

int main(int argc, char **argv) {

    int status = 0;
    auto suite = TestSuite::getSuite();
    for (auto & it : suite) {
        status |= QTest::qExec(it, 0, argv);
    }

    return status;
}
