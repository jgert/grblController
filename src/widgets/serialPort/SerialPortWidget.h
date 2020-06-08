//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QWidget>

namespace Ui {
    class SerialPortWidget;
}

class SerialPortWidget : public QWidget {
Q_OBJECT
private:
    Ui::SerialPortWidget *ui;
    bool reloadingPorts;

    void scanPorts();
    void on_comboBoxSerialPort_currentIndexChanged(int index);

signals:

    void serialPortChange(const QString &name);

    void send(const QString &data);

public:
    explicit SerialPortWidget(QWidget *parent = nullptr);

    ~SerialPortWidget();

};

#endif // FIRSTWIDGET_H
