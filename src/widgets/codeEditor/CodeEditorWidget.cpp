//
// Created by Jakub Gert on 25/08/2020.
//

#include <QPainter>
#include <QTextBlock>
#include "CodeEditorWidget.h"
#include "LineNumberWidget.h"

CodeEditorWidget::CodeEditorWidget(QWidget *parent) :
        QPlainTextEdit(parent),
        lineNumberArea(new LineNumberWidget(this)) {

    connect(
            this, &CodeEditorWidget::blockCountChanged,
            this, &CodeEditorWidget::updateLineNumberAreaWidth);
    connect(
            this, &CodeEditorWidget::updateRequest,
            this, &CodeEditorWidget::updateLineNumberArea);
//    connect(
//            this, &CodeEditorWidget::cursorPositionChanged,
//            this, &CodeEditorWidget::highlightCurrentLine);

    setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    updateLineNumberAreaWidth(0);
}

CodeEditorWidget::~CodeEditorWidget() {
    delete lineNumberArea;
    lineNumberArea = nullptr;
}

int CodeEditorWidget::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    digits = digits < 4 ? 4 : digits;
    int space = 4 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditorWidget::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditorWidget::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditorWidget::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditorWidget::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

//    if (!isReadOnly()) {
    QTextEdit::ExtraSelection selection;

    QColor lineColor = QColor(Qt::lightGray);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);
//    }

    setExtraSelections(extraSelections);
}

void CodeEditorWidget::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);
    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    painter.setFont(font);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            if (breakpoints.contains(block.blockNumber())) {
                painter.setPen(Qt::red);
            } else {
                painter.setPen(Qt::black);
            }
            QString number = QString::number(blockNumber + 1);
            painter.drawText(0, top, lineNumberArea->width() - 2, fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditorWidget::toggleBreakpoint(int lineNumber) {
    QList<QTextEdit::ExtraSelection> selections = extraSelections();

    if (breakpoints.contains(lineNumber)) {
        breakpoints.remove(lineNumber);
    } else {
        breakpoints.insert(lineNumber);
    }
    this->update();
}
