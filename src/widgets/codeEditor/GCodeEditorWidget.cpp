//
// Created by Jakub Gert on 28/09/2020.
//

#include <QDebug>
#include "GCodeEditorWidget.h"

GCodeEditorWidget::GCodeEditorWidget(QWidget *parent) :
        CodeEditorWidget(parent) {

    connect(
            this, &GCodeEditorWidget::textChanged,
            this, &GCodeEditorWidget::onTextChanged);
}

void GCodeEditorWidget::onTextChanged() {

    auto text = document()->toPlainText();
    qDebug() << text;
//    auto program = gpr::parse_gcode(text.toStdString());

//    qDebug() << program.num_blocks();
}