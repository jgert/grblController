//
// Created by Jakub Gert on 07/06/2020.
//

#include "Vec3Widget.h"
#include "ui_Vec3Widget.h"

Vec3Widget::Vec3Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Vec3Widget) {
    ui->setupUi(this);

}

Vec3Widget::~Vec3Widget() {
    delete ui;
}

void Vec3Widget::setTitle(const QString &title) {
    ui->labelTitle->setText(title);
}

void Vec3Widget::setValue(const vec3 &value) {
    ui->lineEditX->setText(QString::number(value.x(), 'f', 4));
    ui->lineEditY->setText(QString::number(value.y(), 'f', 4));
    ui->lineEditZ->setText(QString::number(value.z(), 'f', 4));
}

void Vec3Widget::setReadOnly(bool readOnly) {
    ui->lineEditX->setReadOnly(readOnly);
    ui->lineEditY->setReadOnly(readOnly);
    ui->lineEditZ->setReadOnly(readOnly);
}