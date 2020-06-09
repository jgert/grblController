//
// Created by Jakub Gert on 07/06/2020.
//

#include <QObject>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) :
        QWidget(parent),
        history(new QStringList()),
        historyIndex(0),
        ui(new Ui::ConsoleWidget) {

    ui->setupUi(this);

    ui->pushButtonSend->setText("Send");

    auto *toolbar = new QToolBar();

    actionPaused = new QAction("Paused");
    actionPaused->setCheckable(true);

    actionSaveLog = new QAction("Save log");
    connect(actionSaveLog, &QAction::triggered,
            this, &ConsoleWidget::saveConsoleLog);

    actionClearLog = new QAction("Clear log");
    connect(actionClearLog, &QAction::triggered,
            this, &ConsoleWidget::clearConsole);

    toolbar->addAction(actionPaused);
    toolbar->addAction(actionSaveLog);
    toolbar->addAction(actionClearLog);

    connect(ui->pushButtonSend, &QPushButton::clicked,
            this, &ConsoleWidget::sendMessage);

    ui->lineEditCommand->installEventFilter(this);

    ui->verticalLayout->insertWidget(0, toolbar);
}


bool ConsoleWidget::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->lineEditCommand) {
        if (event->type() == QEvent::KeyPress) {
            auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
            if (keyEvent != nullptr) {
                auto keyCode = keyEvent->key();
                switch (keyCode) {
                    case Qt::Key_Enter:
                    case Qt::Key_Return:
                        sendMessage();
                        return true;
                    case Qt::Key_Up:
                        if (historyIndex > 0) {
                            historyIndex -= 1;
                        }
                        ui->lineEditCommand->setText(history->at(historyIndex));
                        return true;
                    case Qt::Key_Down:
                        if (historyIndex + 1 < history->count()) {
                            historyIndex += 1;
                            ui->lineEditCommand->setText(history->at(historyIndex));
                            return true;
                        } else {
                            ui->lineEditCommand->clear();
                            return true;
                        }
                    default:
                        return QObject::eventFilter(watched, event);
                }
            }
        }
    }
    return QObject::eventFilter(watched, event);
}

ConsoleWidget::~ConsoleWidget() {
    delete ui;
}

void ConsoleWidget::sendMessage() {
    QString text = ui->lineEditCommand->text();

    if (text.isEmpty()) {
        text = ui->lineEditCommand->placeholderText();
    }

    if (history->count() > 0) {
        if (history->last() != text) {
            history->append(text);
        }
    } else {
        history->append(text);
    }
    historyIndex = history->count();

    emit onSendMessage((text + "\n").toLocal8Bit());
    ui->lineEditCommand->setPlaceholderText(text);
    ui->lineEditCommand->clear();
}

void ConsoleWidget::clearConsole() {
    ui->plainTextEdit->clear();
}

void ConsoleWidget::slot_receivedData(const QByteArray &data) {

    if (actionPaused->isChecked())
        return;

    ui->plainTextEdit->appendPlainText(QString(data));
}

void ConsoleWidget::saveConsoleLog() {

    auto fileName = QFileDialog::getSaveFileName(
            this,
            "Save file",
            ".",
            "Text file (*.txt)");

    if (fileName.isEmpty()) {
        return;
    }

    auto *file = new QFile(fileName, this);
    file->open(QIODevice::OpenMode(QIODevice::WriteOnly));
    file->write(QByteArray(ui->plainTextEdit->toPlainText().toUtf8()));
    file->close();
}
