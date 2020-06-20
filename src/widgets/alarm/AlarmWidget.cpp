//
// Created by Jakub Gert on 20/06/2020.
//

#include "AlarmWidget.h"
#include "ui_AlarmWidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::AlarmWidget),
        alarmCodes(new AlarmCodes(":/csv/alarm_codes_en_US.csv")),
        pendingResponse(nullptr) {

    ui->setupUi(this);

    ui->lineEdit->setReadOnly(true);
    ui->label->clear();
    ui->label->setWordWrap(true);

    ui->pushButton->setText("Kill alarm");
    ui->pushButton->setHidden(true);

    connect(ui->pushButton, &QPushButton::pressed,
            this, &AlarmWidget::onKillAlarmClicked);
}

AlarmWidget::~AlarmWidget() {
    delete ui;
    ui = nullptr;

    delete alarmCodes;
    alarmCodes = nullptr;

    delete pendingResponse;
    pendingResponse = nullptr;
}

void AlarmWidget::setAlarm(unsigned int alarmCode) {
    ui->pushButton->setHidden(false);
    AlarmCodeItem item = alarmCodes->getAlarmCodeItem(alarmCode);
    ui->lineEdit->setText("ALARM:" + QString::number(item.code) + " " + item.name);
    ui->label->setText(item.description);
}

void AlarmWidget::onKillAlarmClicked() {

    delete pendingResponse;

    pendingResponse = new Message(Message::messageKillAlarm());
    emit enqueueMessage(*pendingResponse);
}

void AlarmWidget::messageError(const Message &message, unsigned int errorCode) {
    if (pendingResponse && message.id == pendingResponse->id) {
        //TODO: Add error handler here
    }
}

void AlarmWidget::messageOk(const Message &message) {
    if(pendingResponse && message.id == pendingResponse->id) {
        ui->pushButton->setHidden(true);
        ui->label->clear();
        ui->lineEdit->clear();
    }
}
