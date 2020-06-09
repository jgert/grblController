//
// Created by Jakub Gert on 08/06/2020.
//

#ifndef GRBL_WELCOMEWIDGET_H
#define GRBL_WELCOMEWIDGET_H

#include <QWidget>
#include "ui_WelcomeWidget.h"

namespace Ui {
    class WelcomeWidget;
}

class WelcomeWidget : public QWidget {
Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);

    ~WelcomeWidget();

private:
    Ui::WelcomeWidget *ui;

public slots:

    void setVersion(const QString &version);
};

#endif //GRBL_WELCOMEWIDGET_H
