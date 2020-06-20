//
// Created by Jakub Gert on 20/06/2020.
//

#include <QFile>
#include <QDebug>
#include "AlarmCodes.h"

bool AlarmCodes::load(const QString &fileName) {
    map.clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return false;
    }

    // remove first line
    file.readLine();

    QStringList wordList;

    unsigned int lineNumber = 1;

    while (!file.atEnd()) {
        auto line = QString(file.readLine());
        auto list = line.split("\",\"");

        if (list.count() != 3) {
            qDebug() << "Unexpected number of items at line" << QString::number(lineNumber) << ":" << line << "Expected 3, got:" << list.count();
            for(int a=0; a<list.count(); a++) {
                qDebug() << "list["+QString::number(a)+"]=" + list[a];
            }
            return false;
        }

        for (int a = 0; a < list.count(); a++) {
            list[a] = list[a].remove("\"");
        }

        AlarmCodeItem item;
        bool ok = false;
        item.code = list[0].trimmed().toInt(&ok);
        if (!ok) {
            qDebug() << "Expected number at line " << QString::number(lineNumber) << ":" << line;
            return false;
        }

        item.name = list[1].trimmed();
        item.description = list[2].trimmed();

        map[item.code] = item;

        lineNumber += 1;
    }

    return true;
}

AlarmCodes::AlarmCodes(const QString &fileName) {
    load(fileName);
}

AlarmCodeItem AlarmCodes::getAlarmCodeItem(unsigned int code) const {
    if (map.contains(code)) {
        return map[code];
    } else {
        AlarmCodeItem item;
        item.code = code;
        item.name = "";
        item.description = "";
        return item;
    }
}
