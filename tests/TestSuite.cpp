//
// Created by Jakub Gert on 05/06/2020.
//

#include "TestSuite.h"

TestSuite::TestSuite()
{
    getSuite().append(this);
}

QList<QObject *> &TestSuite::getSuite() {
    static QList<QObject*> suite;
    return suite;
}
