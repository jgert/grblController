//
// Created by Jakub Gert on 28/09/2020.
//

#ifndef GRBL_GCODEEDITORWIDGET_H
#define GRBL_GCODEEDITORWIDGET_H

#include "CodeEditorWidget.h"

class GCodeEditorWidget : public CodeEditorWidget {
    Q_OBJECT
public:
    explicit GCodeEditorWidget(QWidget *parent = nullptr);
private slots:
    void onTextChanged();
};


#endif //GRBL_GCODEEDITORWIDGET_H
