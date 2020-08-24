//
// Created by Jakub Gert on 20/06/2020.
//

#ifndef GRBL_ALARMWIDGET_H
#define GRBL_ALARMWIDGET_H

#include <QWidget>
#include <src/grbl/Message.h>
#include <src/utils/ErrorCodes.h>
#include "src/utils/AlarmCodes.h"

namespace Ui {
    class AlarmWidget;
}

class AlarmWidget: public QWidget {
    Q_OBJECT
private:
    Ui::AlarmWidget *ui;
    AlarmCodes *alarmCodes;
    ErrorCodes *errorCodes;
    Message *pendingResponse;
private slots:
    void onKillAlarmClicked();
public:
    explicit AlarmWidget(QWidget *parent = nullptr);
    ~AlarmWidget() override;
signals:
    void enqueueMessage(const Message &message) const;

public slots:
    void setAlarm(unsigned int alarmCode);
    void messageError(const Message &message, unsigned int errorCode);
    void messageOk(const Message &message);
};

#endif //GRBL_ALARMWIDGET_H
