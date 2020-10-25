//
// Created by Jakub Gert on 28/09/2020.
//

#include <QThreadPool>
#include <QThread>
#include <QDebug>
#include <src/gCode/Parser.h>
#include <src/machine/Engraver3axis.h>
#include "GCodeEditorWidget.h"
#include "src/widgets/render/Renderer3DWidget.h"

GCodeEditorWidget::GCodeEditorWidget(QWidget *parent) :
        CodeEditorWidget(parent),
        highlighter(new GCodeSyntaxHighlighter(this->document())),
        machine(new Engraver3axis()) {

    connect(this, &QPlainTextEdit::textChanged,
            this, &GCodeEditorWidget::onTextChanged);
}

GCodeEditorWidget::~GCodeEditorWidget() {
    delete highlighter;
    highlighter = nullptr;
}

void GCodeEditorWidget::onTextChanged() {
    parse();
}

void GCodeEditorWidget::setMachine(Machine *m) {
    this->machine = m;
    if (machine) {
        machine->reset();
        parse();
    }
}

void GCodeEditorWidget::parse() {

    auto program = document()->toPlainText().toStdString();

    auto result = parser.parse(program);

//    if (!result) {
//        return;
//    }

    if (!machine) {
        return;
    }

    result = machine->parse(parser.blocks());

//    if (!result) {
//        return;
//    }

    QVector<Line> lines;
    for (auto const &op: machine->getOperations()) {
        switch (op.type) {
            case Operation::Move:
                lines.append(
                        Line(
                                Vertex(op.operationMove.from, QVector4D(0, 0, 0, 1)),
                                Vertex(op.operationMove.to, QVector4D(0, 0, 0, 1))));
                break;
        }
    }

    emit producedLines(lines);
}
