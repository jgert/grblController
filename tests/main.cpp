//
// Created by Jakub Gert on 07/06/2020.
//

#include <QTest>
#include "tests/TestSuite.h"

using namespace std;

int main(int argc, char **argv) {

    int status = 0;
    auto suite = TestSuite::getSuite();
    for (auto & it : suite) {
        status += QTest::qExec(it, argc, argv);
    }

    return status;
}
