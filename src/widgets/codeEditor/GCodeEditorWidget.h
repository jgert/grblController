//
// Created by Jakub Gert on 28/09/2020.
//

#ifndef GRBL_GCODEEDITORWIDGET_H
#define GRBL_GCODEEDITORWIDGET_H

#include "CodeEditorWidget.h"
#include "GCodeSyntaxHighlighter.h"

class GCodeEditorWidget : public CodeEditorWidget {
    Q_OBJECT
private:
    GCodeSyntaxHighlighter *highlighter;
public:
    explicit GCodeEditorWidget(QWidget *parent = nullptr);
    virtual ~GCodeEditorWidget();
};


#endif //GRBL_GCODEEDITORWIDGET_H
