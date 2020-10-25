//
// Created by Jakub Gert on 28/09/2020.
//

#ifndef GRBL_GCODEEDITORWIDGET_H
#define GRBL_GCODEEDITORWIDGET_H

#include "CodeEditorWidget.h"
#include "GCodeSyntaxHighlighter.h"
#include "../machine/Machine.h"

struct Line;

class GCodeEditorWidget : public CodeEditorWidget {
Q_OBJECT
private:
    gCode::Parser parser;
    GCodeSyntaxHighlighter *highlighter;
    Machine *machine;

    void onTextChanged();

    void parse();

public:
    explicit GCodeEditorWidget(QWidget *parent = nullptr);

    virtual ~GCodeEditorWidget();

    void setMachine(Machine *machine);


signals:

    void producedLines(const QVector<Line> &lines) const;
};


#endif //GRBL_GCODEEDITORWIDGET_H
