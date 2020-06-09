//
// Created by Jakub Gert on 08/06/2020.
//

#include "WelcomeWidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::WelcomeWidget) {
    ui->setupUi(this);

    ui->label->setText("GRBL version");
    ui->lineEdit->setReadOnly(true);
}

WelcomeWidget::~WelcomeWidget() {
    delete ui;
}

void WelcomeWidget::setVersion(const QString &version) {
    ui->lineEdit->setText(version);
}
