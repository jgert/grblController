//
// Created by Jakub Gert on 25/08/2020.
//

#ifndef GRBL_CODEEDITORWIDGET_H
#define GRBL_CODEEDITORWIDGET_H

#include <QPlainTextEdit>

class CodeEditorWidget : public QPlainTextEdit
{
Q_OBJECT

public:
    explicit CodeEditorWidget(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void toggleBreakpoint(int lineNumber);
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
    QSet<int> breakpoints;
};

#endif //GRBL_CODEEDITORWIDGET_H
