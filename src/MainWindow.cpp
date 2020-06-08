//
// Created by Jakub Gert on 07/06/2020.
//

#include <QVBoxLayout>
#include <QDockWidget>
#include <QDebug>
#include <Qt>
#include <QMenu>
#include <QMenuBar>
#include "status/StatusWidget.h"
#include "MainWindow.h"

MainWindow::MainWindow(SerialPort *serialPort) :
        grbl(new GRBL()),
        serialPort(serialPort),
        widgetTools(new QSet<QDockWidget *>),
        serialPortWidget(new SerialPortWidget()),
        consoleWidget(new ConsoleWidget()),
        statusWidget(new StatusWidget()) {

    createMainMenu();

    QDockWidget *dockWidget;

    dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Serial port");
    dockWidget->setWidget(serialPortWidget);
    addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, dockWidget);
    registerDockTool(dockWidget);

    dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Console");
    dockWidget->setWidget(consoleWidget);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dockWidget);
    registerDockTool(dockWidget);
    connect(
            consoleWidget, &ConsoleWidget::onSendMessage,
            serialPort, &SerialPort::send);

    dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Status");
    dockWidget->setWidget(statusWidget);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dockWidget);
    registerDockTool(dockWidget);

    connect(grbl, &GRBL::onReceivedAccessoryState,
            statusWidget, &StatusWidget::setAccessoryState);
    connect(grbl, &GRBL::onReceivedBufferState,
            statusWidget, &StatusWidget::setBufferState);
    connect(grbl, &GRBL::onReceivedFeedRate,
            statusWidget, &StatusWidget::setFeedRate);
    connect(grbl, &GRBL::onReceivedSpindleSpeed,
            statusWidget, &StatusWidget::setSpindleSpeed);
    connect(grbl, &GRBL::onReceivedInputPinState,
            statusWidget, &StatusWidget::setInputPinState);
    connect(grbl, &GRBL::onReceivedLineNumber,
            statusWidget, &StatusWidget::setLineNumber);
    connect(grbl, &GRBL::onReceivedMachineState,
            statusWidget, &StatusWidget::setMachineState);
    connect(grbl, &GRBL::onReceivedOverriddenValues,
            statusWidget, &StatusWidget::setOverriddenValues);
    connect(grbl, &GRBL::onReceivedMPos,
            statusWidget, &StatusWidget::setMachinePosition);
    connect(grbl, &GRBL::onReceivedWPos,
            statusWidget, &StatusWidget::setWorkPosition);
    connect(grbl, &GRBL::onReceivedWorkCoordinateOffset,
            statusWidget, &StatusWidget::setWorkCoordinateOffset);

    setCentralWidget(nullptr);
    setDockOptions(DockOption::AllowNestedDocks | DockOption::AnimatedDocks);

    connectSerialPort();
}

void MainWindow::createMainMenu() {
    setMenuBar(new QMenuBar());
    createMenuTools();
}

void MainWindow::createMenuTools() {
    menuTools = new QMenu("Tools");
    menuBar()->addMenu(menuTools);

    actionFloatingDocks = menuTools->addAction("Floating docks");
    actionFloatingDocks->setCheckable(true);
    actionFloatingDocks->setChecked(true);

    connect(actionFloatingDocks, &QAction::triggered,
            this, &MainWindow::actionFloatingDocks_checked);

    menuTools->addSeparator();
}

void MainWindow::registerDockTool(QDockWidget *widget) {
    widgetTools->insert(widget);

    QAction *action;
    qDebug() << widget->windowTitle();
    action = menuTools->addAction(widget->windowTitle());
    action->setCheckable(true);
    action->setChecked(true);

    connect(
            widget, &QDockWidget::visibilityChanged,
            [action](bool visible) {
                action->setChecked(visible);
            });

    connect(
            action, &QAction::triggered,
            [widget](bool checked) {
                widget->setHidden(!checked);
            });
}

void MainWindow::connectSerialPort() const {

    connect(
            serialPortWidget, &SerialPortWidget::serialPortChange,
            serialPort, &SerialPort::openPort);
    connect(
            serialPort, &SerialPort::receivedData,
            consoleWidget, &ConsoleWidget::slot_receivedData);
    connect(
            serialPort, &SerialPort::receivedData,
            grbl, &GRBL::parse);
}

void MainWindow::actionFloatingDocks_checked(bool checked) {
    QSetIterator<QDockWidget *> iterator(*widgetTools);
    while (iterator.hasNext()) {
        QDockWidget *widget = iterator.next();
        if (checked) {
            widget->setTitleBarWidget(nullptr);
        } else {
            widget->setTitleBarWidget(new QWidget());
        }
    }
}
