//
// Created by Jakub Gert on 10/06/2020.
//

#include <QObject>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include "SettingsWidget.h"
#include "SettingsTableModel.h"
#include "../delegates/LineEditItemDelegate.h"
#include "ui_settingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
        QWidget(parent),
        model(new SettingsTableModel()),
        ui(new Ui::SettingsWidget) {

    ui->setupUi(this);

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->setItemDelegateForColumn(SettingsTableModel::Col::Value, new LineEditItemDelegate());

    connect(model, &SettingsTableModel::onSettingChange,
            this, &SettingsWidget::settingItemUpdated);
}

SettingsWidget::~SettingsWidget() {
    delete ui;
    delete model;
}

void SettingsWidget::setSettingItem(const SettingItem &settingItem) {
    model->setSettingItem(settingItem);
}

void SettingsWidget::settingItemUpdated(const SettingItem &item) {
    emit enqueueMessage(Message::messageSetSetting(item));
    emit enqueueMessage(Message::messageSettings());
}
