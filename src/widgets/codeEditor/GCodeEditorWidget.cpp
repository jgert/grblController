//
// Created by Jakub Gert on 28/09/2020.
//

#include <QDebug>
#include <src/gCode/Parser.h>
#include "GCodeEditorWidget.h"

GCodeEditorWidget::GCodeEditorWidget(QWidget *parent) :
        CodeEditorWidget(parent),
        highlighter(new GCodeSyntaxHighlighter(this->document())) {
}

GCodeEditorWidget::~GCodeEditorWidget() {
    delete highlighter;
    highlighter = nullptr;
}
