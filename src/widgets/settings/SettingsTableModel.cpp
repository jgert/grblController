//
// Created by Jakub Gert on 11/06/2020.
//

#include <QDebug>
#include <QColor>
#include "SettingsTableModel.h"

int SettingsTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return items.count();
}

int SettingsTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return Col::LAST;
}

bool SettingsTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if (role != Qt::EditRole) {
        return QAbstractItemModel::setData(index, value, role);
    }

    if (index.column() != Col::Value) {
        return false;
    }

    auto key = items.keys()[index.row()];
    auto item = items[key];

    item.value = value.toString().toStdString();
    items[key] = item;

    overriddenItems[key] = item;

    emit onSettingChange(item);

    return true;
}

QVariant SettingsTableModel::data(const QModelIndex &index, int role) const {

    const auto keys = items.keys();
    const auto key = keys[index.row()];
    const SettingItem settingItem = items[key];
    const auto settingCode = codes->getSettingCodeItem(settingItem.code);

    switch (role) {
        case Qt::ItemDataRole::DisplayRole:
        case Qt::ItemDataRole::EditRole: {

            switch (index.column()) {
                case Col::Name:
                    return QVariant(settingCode.name);
                case Col::Value:
                    return QVariant(QString(settingItem.value.c_str()));
                case Col::Unit:
                    return QVariant(settingCode.unit);
                case Col::Description:
                    return QVariant(settingCode.description);
                default:
                    return QVariant();
            }
        }
        case Qt::ItemDataRole::BackgroundRole: {
            if(overriddenItems.contains(key)) {
                qDebug() << overriddenItems[key].value.c_str() << settingItem.value.c_str();
                return QVariant(QColor(255, 0, 0));
            } else {
                return QVariant();
            }
        }
        default:
            return QVariant();
    }
}

QVariant SettingsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (orientation == Qt::Orientation::Horizontal) {
            switch (section) {
                case Col::Name:
                    return QVariant("Name");
                case Col::Value:
                    return QVariant("Value");
                case Col::Unit:
                    return QVariant("Unit");
                case Col::Description:
                    return QVariant("Description");
                default:
                    return QVariant();
            }
        } else {
            const auto keys = items.keys();
            const SettingItem item = items[keys[section]];
            return QVariant("$" + QString::number(item.code));
        }
    } else {
        return QVariant();
    }
}

void SettingsTableModel::setSettingItem(const SettingItem &configurationItem) {
    beginResetModel();
    unsigned int code = configurationItem.code;
    items[code] = configurationItem;
    if(overriddenItems.contains(code) && overriddenItems[code].value == configurationItem.value) {
        overriddenItems.remove(code);
    }
    endResetModel();
}

SettingsTableModel::SettingsTableModel() :
        codes(new SettingCodes(":/csv/setting_codes_en_US.csv")) {
}

SettingsTableModel::~SettingsTableModel() {
    delete codes;
    codes = nullptr;
}

Qt::ItemFlags SettingsTableModel::flags(const QModelIndex &index) const {

    Qt::ItemFlags flags = Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemNeverHasChildren;
    if (index.column() == Col::Value) {
        flags |= Qt::ItemFlag::ItemIsEditable;
    }

    return flags;
}

