//
// Created by Jakub Gert on 11/06/2020.
//

#ifndef GRBL_SETTINGSTABLEMODEL_H
#define GRBL_SETTINGSTABLEMODEL_H

#include <QAbstractTableModel>
#include <src/grbl/parsers/setting/SettingParser.h>
#include "SettingCodes.h"

class SettingsTableModel: public QAbstractTableModel {
    Q_OBJECT
    QMap<unsigned int, SettingItem> overriddenItems;
    QMap<unsigned int, SettingItem> items;
    SettingCodes *codes;

public:

    enum Col {
        Name,
        Value,
        Unit,
        Description,
        LAST
    };

    explicit SettingsTableModel();
    virtual ~SettingsTableModel();

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
//
    QVariant data(const QModelIndex &index, int role) const override;
//
    void setSettingItem(const SettingItem &configurationItem);

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

signals:
    void onSettingChange(const SettingItem &item) const;
};



#endif //GRBL_SETTINGSTABLEMODEL_H
