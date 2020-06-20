//
// Created by Jakub Gert on 10/06/2020.
//

#ifndef GRBL_CONFIGURATIONWIDGET_H
#define GRBL_CONFIGURATIONWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <src/grbl/parsers/setting/SettingParser.h>
#include <src/grbl/Message.h>
#include "SettingsTableModel.h"

namespace Ui {
    class SettingsWidget;
}

class SettingsWidget : public QWidget {
Q_OBJECT
private:
    SettingsTableModel *model;

    void settingItemUpdated(const SettingItem &item);

public:

    explicit SettingsWidget(QWidget *parent = nullptr);

    ~SettingsWidget();

    void setSettingItem(const SettingItem &settingItem);

private:
    Ui::SettingsWidget *ui;

signals:

    void enqueueMessage(const Message &message) const;
};


#endif //GRBL_CONFIGURATIONWIDGET_H
