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
        menuTools(nullptr),
        actionFloatingDocks(nullptr),
        widgetTools(new QSet<QDockWidget *>),
        serialPortWidget(new SerialPortWidget()),
        consoleWidget(new ConsoleWidget()),
        statusWidget(new StatusWidget()),
        welcomeWidget(new WelcomeWidget()),
        settingsWidget(new SettingsWidget()),
        alarmWidget(new AlarmWidget()) {

    createMainMenu();

    createToolSerialPort();
    createToolWelcome();
    createToolConsole();
    createToolSettings();
    createToolStatus();
    createToolAlarm();

    setCentralWidget(nullptr);
    setDockOptions(DockOption::AllowNestedDocks | DockOption::AnimatedDocks);

    connect(grbl, &GRBL::onParserError,
            consoleWidget, &ConsoleWidget::addMessage);

    connect(grbl, &GRBL::send,
            serialPort, &SerialPort::send);

    connect(
            serialPort, &SerialPort::receivedData,
            grbl, &GRBL::parse);


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
    action = menuTools->addAction(widget->windowTitle());
    action->setMenuRole(QAction::NoRole);
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

void MainWindow::createToolSettings() {
    auto dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Settings");
    dockWidget->setWidget(settingsWidget);
    addDockWidget(
            Qt::DockWidgetArea::RightDockWidgetArea,
            dockWidget);
    registerDockTool(dockWidget);
    connect(grbl, &GRBL::onReceivedSetting,
            settingsWidget, &SettingsWidget::setSettingItem);
    connect(settingsWidget, &SettingsWidget::enqueueMessage,
            grbl, &GRBL::enqueue);
}

void MainWindow::createToolConsole() {
    auto dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Console");
    dockWidget->setWidget(consoleWidget);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockWidget);
    registerDockTool(dockWidget);

    connect(consoleWidget, &ConsoleWidget::enqueueMessage,
            grbl, &GRBL::enqueue);

    connect(grbl, &GRBL::onMessageEnqueued,
            consoleWidget, &ConsoleWidget::messageEnqueued);

    connect(grbl, &GRBL::onMessageSent,
            consoleWidget, &ConsoleWidget::messageSent);

    connect(grbl, &GRBL::onMessageError,
            consoleWidget, &ConsoleWidget::messageError);

    connect(grbl, &GRBL::onMessageOk,
            consoleWidget, &ConsoleWidget::messageOk);
}

void MainWindow::createToolSerialPort() {
    auto dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Serial port");
    dockWidget->setWidget(serialPortWidget);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockWidget);

    registerDockTool(dockWidget);

    connect(
            serialPortWidget, &SerialPortWidget::serialPortChange,
            serialPort, &SerialPort::openPort);
}

void MainWindow::createToolWelcome() {
    auto dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Welcome");
    dockWidget->setWidget(welcomeWidget);
    addDockWidget(
            Qt::DockWidgetArea::LeftDockWidgetArea,
            dockWidget);
    registerDockTool(dockWidget);

    connect(grbl, &GRBL::onReceivedWelcomeMessage,
            welcomeWidget, &WelcomeWidget::setVersion);
}

void MainWindow::createToolStatus() {

    auto dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Status");
    dockWidget->setWidget(statusWidget);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dockWidget);
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
}

void MainWindow::createToolAlarm() {
    auto dockWidget = new QDockWidget();
    dockWidget->setWindowTitle("Alarm");
    dockWidget->setWidget(alarmWidget);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dockWidget);
    registerDockTool(dockWidget);

    connect(grbl, &GRBL::onReceivedAlarm,
            alarmWidget, &AlarmWidget::setAlarm);

    connect(alarmWidget, &AlarmWidget::enqueueMessage,
            grbl, &GRBL::enqueue);

    connect(grbl, &GRBL::onMessageOk,
            alarmWidget, &AlarmWidget::messageOk);

    connect(grbl, &GRBL::onMessageError,
            alarmWidget, &AlarmWidget::messageError);
}
