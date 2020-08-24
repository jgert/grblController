//
// Created by Jakub Gert on 12/06/2020.
//

#ifndef GRBL_SETTINGCODES_H
#define GRBL_SETTINGCODES_H

#include <QMap>

struct SettingCodeItem {
    unsigned int code;
    QString name;
    QString unit;
    QString description;
};

class SettingCodes {
    QMap<unsigned int, SettingCodeItem> map;
private:
    bool load(const QString &fileName);

public:
    explicit SettingCodes(const QString &fileName);

    SettingCodeItem getSettingCodeItem(unsigned int code) const;
};


#endif //GRBL_SETTINGCODES_H
