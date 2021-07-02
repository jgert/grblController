//
// Created by Jakub Gert on 25/08/2020.
//

#ifndef GRBL_LINENUMBERWIDGET_H
#define GRBL_LINENUMBERWIDGET_H


#include <QWidget>
#include <QDebug>
#include "CodeEditorWidget.h"

class LineNumberWidget : public QWidget {
public:
    LineNumberWidget(CodeEditorWidget *editor) : QWidget(editor), codeEditor(editor) {}

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

    void mousePressEvent(QMouseEvent *event) override {
        QWidget::mousePressEvent(event);
        QTextCursor tc = codeEditor->cursorForPosition(event->pos());
        codeEditor->toggleBreakpoint(tc.blockNumber());
    }

private:
    CodeEditorWidget *codeEditor;
};

#endif //GRBL_LINENUMBERWIDGET_H
