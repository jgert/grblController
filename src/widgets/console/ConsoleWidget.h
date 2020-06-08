//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>

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

    void slot_receivedData(const QByteArray &data);

signals:
    void onSendMessage(const QByteArray &data);
};

#endif // CONSOLEWIDGET_H
