//
// Created by Jakub Gert on 07/06/2020.
//

#include <iostream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qdebug.h>
#include "SerialPortWidget.h"
#include "ui_SerialPortWidget.h"

SerialPortWidget::SerialPortWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SerialPortWidget),
        reloadingPorts(false) {

    ui->setupUi(this);

    connect(ui->pushButtonReload, &QPushButton::clicked,
            this, &SerialPortWidget::scanPorts);
    connect(ui->comboBoxSerialPort, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &SerialPortWidget::on_comboBoxSerialPort_currentIndexChanged);

    scanPorts();
}

SerialPortWidget::~SerialPortWidget() {
    delete ui;
}

void SerialPortWidget::scanPorts() {
    reloadingPorts = true;
    const QString selectedText = ui->comboBoxSerialPort->currentText();
    int indexToSelect = -1;
    QStringList list;

    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for(int a=0; a<ports.count(); a++) {
        const QSerialPortInfo info = ports[a];
        list.append(info.portName());
        if (info.portName() == selectedText) {
            indexToSelect = a;
        }
    }
    ui->comboBoxSerialPort->clear();
    ui->comboBoxSerialPort->addItems(list);
    reloadingPorts = false;
    ui->comboBoxSerialPort->setCurrentIndex(indexToSelect);
}

void SerialPortWidget::on_comboBoxSerialPort_currentIndexChanged(int index)
{
    qDebug() << "item changed " << index;
    if (!reloadingPorts) {

        const QString name = ui->comboBoxSerialPort->currentText();
        emit serialPortChange(name);
    }
}
