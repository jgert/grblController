//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef VIEWER_MAINWINDOW_H
#define VIEWER_MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <src/widgets/console/ConsoleWidget.h>
#include <src/grbl/GRBL.h>
#include "SerialPort.h"
#include "src/widgets/serialPort/SerialPortWidget.h"
#include "status/StatusWidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    GRBL *grbl;
    SerialPort *serialPort;
    QMenu *menuTools;
    QAction *actionFloatingDocks;
    QSet<QDockWidget *> *widgetTools;
    SerialPortWidget *serialPortWidget;
    ConsoleWidget *consoleWidget;
    StatusWidget *statusWidget;

    void createMainMenu();

    void createMenuTools();

    void actionFloatingDocks_checked(bool checked);

    void registerDockTool(QDockWidget *widget);

private slots:

    void connectSerialPort() const;

public:
    explicit MainWindow(SerialPort *serialPort);
};

#endif //VIEWER_MAINWINDOW_H
