//
// Created by Jakub Gert on 13/05/2020.
//

#ifndef VIEWER_SERIALPORT_H
#define VIEWER_SERIALPORT_H

#include <QSerialPort>
#include <QObject>

class SerialPort : public QObject {
Q_OBJECT
private:
    QSerialPort *serialPort;
    bool paused;

    void closePort();

private slots:

    void readData();

public:
    SerialPort();
    virtual ~SerialPort();

    void openPort(const QString &name);

public slots:

    void setPaused(bool paused);

    void send(const QByteArray &array);
signals:

    void receivedData(const QByteArray &array) const;
};


#endif //VIEWER_SERIALPORT_H
