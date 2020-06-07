//
// Created by Jakub Gert on 05/06/2020.
//

#ifndef GRBL_TESTSUITE_H
#define GRBL_TESTSUITE_H

#include <QObject>

class TestSuite: public QObject
{
public:
    TestSuite();

    static QList<QObject*> &getSuite();
};


#endif //GRBL_TESTSUITE_H
