//
// Created by Jakub Gert on 20/06/2020.
//

#ifndef GRBL_ALARMCODES_H
#define GRBL_ALARMCODES_H

#include <QString>
#include <QMap>

struct AlarmCodeItem {
        unsigned int code;
        QString name;
        QString description;
};

class AlarmCodes {
    QMap<unsigned int, AlarmCodeItem> map;
private:
    bool load(const QString &fileName);

public:
    explicit AlarmCodes(const QString &fileName);

    AlarmCodeItem getAlarmCodeItem(unsigned int code) const;
};

#endif //GRBL_ALARMCODES_H
