//
// Created by Jakub Gert on 16/06/2020.
//

#include <QString>
#include <QStringList>
#include "Message.h"

Message Message::messageInfo() {
    return Message("$I\n");
}

Message Message::messageSettings() {
    return Message("$$\n");
}

Message::Message(const QByteArray &data) : data(data) {

    static unsigned int messageID = 0;

    this->id = messageID;

    messageID += 1;
}

Message Message::custom(const QString &message) {
    return Message(message.toLocal8Bit());
}

Message Message::messageSetSetting(const SettingItem &item) {
    QStringList list;
    list
            << "$"
            << QString::number(item.code)
            << "="
            << QString(item.value.c_str())
            << "\n";

    return Message(list.join("").toLocal8Bit());
}
