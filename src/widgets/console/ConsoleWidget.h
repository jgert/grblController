//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <src/grbl/Message.h>
#include <src/utils/ErrorCodes.h>

namespace Ui {
    class ConsoleWidget;
}

class ConsoleWidget : public QWidget {
Q_OBJECT

private:
    QAction *actionPaused;
    QAction *actionSaveLog;
    QAction *actionClearLog;
    QStringList *history;
    int historyIndex;
    ErrorCodes *errorCodes;
    void clearConsole();
    void saveConsoleLog();
    void sendMessage();
public:
    explicit ConsoleWidget(QWidget *parent = nullptr);

    bool eventFilter(QObject *watched, QEvent *event) override;

    ~ConsoleWidget();

private:
    Ui::ConsoleWidget *ui;

public slots:

    void addMessage(const QString &message);

    void messageEnqueued(const Message &message);
    void messageSent(const Message &message);
    void messageError(const Message &message, unsigned int errorCode);
    void messageOk(const Message &message);

signals:
    void enqueueMessage(const Message &message);
};

#endif // CONSOLEWIDGET_H
