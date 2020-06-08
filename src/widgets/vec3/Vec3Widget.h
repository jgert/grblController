//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef VEC3WIDGET_H
#define VEC3WIDGET_H

#include <QWidget>
#include "src/grbl/vec3/vec3.h"

namespace Ui {
class Vec3Widget;
}

class Vec3Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Vec3Widget(QWidget *parent = nullptr);
    ~Vec3Widget();

public slots:
    void setTitle(const QString &title);
    void setValue(const vec3 &value);
    void setReadOnly(bool readOnly);

private:
    Ui::Vec3Widget *ui;
};

#endif // VEC3WIDGET_H
