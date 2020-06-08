//
// Created by Jakub Gert on 13/05/2020.
//

#include <QString>
#include <QDebug>
#include <QThread>
#include "SerialPort.h"

SerialPort::SerialPort() :
        paused(false),
        serialPort(nullptr){

}

SerialPort::~SerialPort() {
    closePort();
}

void SerialPort::closePort() {
    if (serialPort && serialPort->isOpen()) {
        serialPort->close();
    }

    delete serialPort;
    serialPort = nullptr;
}

void SerialPort::openPort(const QString &name) {
    if (serialPort && serialPort->isOpen()) {
        closePort();
    }

    if (name.isEmpty()) {
        return;
    }

    serialPort = new QSerialPort(name);
    serialPort->setBaudRate(115200);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort, &QSerialPort::readyRead, this, &SerialPort::readData, Qt::QueuedConnection);
}

void SerialPort::readData() {
    while(serialPort->canReadLine()) {
        const QByteArray data = serialPort->readLine().trimmed();

        if (paused) {
            return;
        }

        qDebug() << data;
        emit receivedData(data);
    }
}

void SerialPort::setPaused(bool paused) {
    this->paused = paused;
}

void SerialPort::send(const QByteArray &array) {
    if (serialPort == nullptr || !serialPort->isOpen()) {
        return;
    }

    serialPort->write(array);
}