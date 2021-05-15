//
// Created by Jakub Gert on 28/09/2020.
//

#include <cmath>
#include <src/gCode/Parser.h>
#include <src/machine/Engraver3axis.h>
#include "GCodeEditorWidget.h"
#include "src/widgets/render/Renderer3DWidget.h"

GCodeEditorWidget::GCodeEditorWidget(QWidget *parent) :
        CodeEditorWidget(parent),
        highlighter(new GCodeSyntaxHighlighter(this->document())),
        machine(new machine::Engraver3axis()) {

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

void GCodeEditorWidget::setMachine(machine::Machine *m) {
    this->machine = m;
    if (machine) {
        machine->reset();
        parse();
    }
}

void GCodeEditorWidget::parse() {

    auto program = document()->toPlainText().toStdString();

    auto result = parser.parse(program);

    if (!result) {
        qDebug() << "Error parsing program";
        return;
    } else {
        qDebug() << "Parsing done";
    }

    if (!machine) {
        return;
    }

    result = machine->parse(parser.blocks());

    if (!result) {
        qDebug() << "Error machine parse program";
        auto error = machine->error();
        qDebug() << error.description().c_str();
        return;
    } else {
        qDebug() << "Machine parsing done successfully";
    }

    QVector<Line> lines;
    QVector<Vertex> points;
    for (auto const &state : machine->getStates()) {
        const auto &operation = state.operation;
        switch (operation.type) {
            case machine::Operation::NoOperation:
                continue;
            case machine::Operation::Move:
                lines.append(
                        Line(
                                Vertex(operation.operationMove.from, QVector4D(0, 0, 0, 1)),
                                Vertex(operation.operationMove.to, QVector4D(0, 0, 0, 1))));
                break;
            case machine::Operation::Arc:
                lines.append(GCodeEditorWidget::expandArc(state));
                break;
        }
    }

    emit producedLines(lines, points);
}

QVector<Line> GCodeEditorWidget::expandArc(const machine::MachineState &state) {

    const auto &operation = state.operation.operationArc;

    QVector2D from(operation.from[operation.axis_0], operation.from[operation.axis_1]);
    QVector2D to(operation.to[operation.axis_0], operation.to[operation.axis_1]);
    QVector2D center(operation.center[operation.axis_0], operation.center[operation.axis_1]);
    center += from;

    QVector2D r1 = from - center;
    QVector2D r2 = to - center;

    auto startAngle = atan2(r1.y(), r1.x());
    auto angle = atan2(r1.x() * r2.y() - r2.x() * r1.y(), r1.x() * r2.x() + r1.y() * r2.y());

    static const auto PI = atanf(1.0)*4;

    if (operation.clockwise) {
        if (angle > 0) {
            angle -= 2 * PI;
        }
        if (angle == 0.0f) {
            angle = -2.0f * PI;
        }
    } else {
        if (angle < 0) {
            angle += 2 * PI;
        }
        if (angle == 0.0f) {
            angle = 2.0f * PI;
        }
    }

    auto segments = 16;

    float theta_per_segment = angle / (float) segments;
    float linear_per_segment =
            (operation.to[operation.axis_linear] - operation.from[operation.axis_linear]) / (float) segments;

    auto lines = QVector<Line>();

    for (int i = 1; i <= segments; i++) {
        auto x1 = operation.radius * cos((float) (i - 1) * theta_per_segment + startAngle);
        auto y1 = operation.radius * sin((float) (i - 1) * theta_per_segment + startAngle);
        auto x2 = operation.radius * cos((float) (i) * theta_per_segment + startAngle);
        auto y2 = operation.radius * sin((float) (i) * theta_per_segment + startAngle);
        auto z1 = operation.from[operation.axis_linear] + linear_per_segment * (float) (i - 1);
        auto z2 = operation.from[operation.axis_linear] + linear_per_segment * (float) i;
        auto p1 = QVector3D();
        p1[operation.axis_0] = operation.center[operation.axis_0] + x1 + operation.from[operation.axis_0];
        p1[operation.axis_1] = operation.center[operation.axis_1] + y1 + operation.from[operation.axis_1];
        p1[operation.axis_linear] = operation.center[operation.axis_linear] + z1;
        auto p2 = QVector3D();
        p2[operation.axis_0] = operation.center[operation.axis_0] + x2 + operation.from[operation.axis_0];
        p2[operation.axis_1] = operation.center[operation.axis_1] + y2 + operation.from[operation.axis_1];
        p2[operation.axis_linear] = operation.center[operation.axis_linear] + z2;
        lines.append(
                Line(
                        Vertex(p1, QVector4D(0, 0, 0, 1)),
                        Vertex(p2, QVector4D(0, 0, 0, 1))));
    }

    return lines;
}
