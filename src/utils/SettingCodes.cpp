//
// Created by Jakub Gert on 12/06/2020.
//

#include <QFile>
#include <QDebug>
#include "SettingCodes.h"

SettingCodes::SettingCodes(const QString &fileName) {
    load(fileName);
}

bool SettingCodes::load(const QString &fileName) {
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
        auto list = line.split(',');

        if (list.count() != 4) {
            qDebug() << "Unexpected number of items at line" << QString::number(lineNumber) << ":" << line;
            return false;
        }

        for (int a = 0; a < list.count(); a++) {
            list[a] = list[a].remove("\"");
        }

        SettingCodeItem item;
        bool ok = false;
        item.code = list[0].trimmed().toInt(&ok);
        if (!ok) {
            qDebug() << "Expected number at line " << QString::number(lineNumber) << ":" << line;
            return false;
        }

        item.name = list[1].trimmed();
        item.unit = list[2].trimmed();
        item.description = list[3].trimmed();

        map[item.code] = item;

        lineNumber += 1;
    }

    return true;
}

SettingCodeItem SettingCodes::getSettingCodeItem(unsigned int code) const {

    if (map.contains(code)) {
        return map[code];
    } else {
        SettingCodeItem item;
        item.code = code;
        item.name = "";
        item.description = "";
        item.unit = "";
        return item;
    }
}
