//
// Created by Jakub Gert on 07/06/2020.
//

#include <src/grbl/parsers/status_report/accessory_state/AccessoryStateParser.h>
#include <src/grbl/parsers/status_report/buffer_state/BufferStateParser.h>
#include <src/grbl/vec3/vec3.h>
#include "StatusWidget.h"
#include "ui_StatusWidget.h"

StatusWidget::StatusWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StatusWidget) {
    ui->setupUi(this);

    ui->widgetMPos->setTitle("Machine position");
    ui->widgetMPos->setReadOnly(true);

    ui->widgetWPos->setTitle("Work position");
    ui->widgetWPos->setReadOnly(true);

    ui->widgetWCO->setTitle("WCO");
    ui->widgetWCO->setReadOnly(true);

    ui->labelAccesorryState->setText("Accessory state");
    ui->lineEditAccessoryState->setReadOnly(true);

    ui->labelBufferState->setText("Buffer state");
    ui->lineEditBufferState->setReadOnly(true);

    ui->labelFeedRate->setText("Feed rate");
    ui->lineEditFeedRate->setReadOnly(true);

    ui->labelSpindleSpeed->setText("Spindle speed");
    ui->lineEditSpindleSpeed->setReadOnly(true);

    ui->labelInputPinState->setText("Input pin state");
    ui->lineEditInputPinState->setReadOnly(true);

    ui->labelLineNumber->setText("Line number");
    ui->lineEditLineNumber->setReadOnly(true);

    ui->labelMachineState->setText("Machine state");
    ui->lineEditMachineState->setReadOnly(true);

    ui->labelOverriddenValues->setText("Overridden values");
    ui->lineEditOverridenValues->setReadOnly(true);
}

StatusWidget::~StatusWidget() {
    delete ui;
}

void StatusWidget::setAccessoryState(AccessoryState state) {
    QStringList text;
    switch (state.spindleState) {
        case AccessoryState::enabledCCW:
            text << "S:CCW";
            break;
        case AccessoryState::enabledCW:
            text << "S:CW";
            break;
        case AccessoryState::off:
            text << "S:OFF";
            break;
    }
    if (state.mistCoolant) {
        text << "MC:ON";
    } else {
        text << "MC:OFF";
    }
    if (state.floodCoolant) {
        text << "FC:ON";
    } else {
        text << "FC:OFF";
    }

    ui->lineEditAccessoryState->setText(text.join(" "));
}

void StatusWidget::setBufferState(BufferState bufferState) {
    QStringList text;

    text << "AB:" + QString::number(bufferState.availableBlocks);
    text << "RX:" + QString::number(bufferState.availableBytesInRxBuffer);

    ui->lineEditBufferState->setText(text.join(" "));
}

void StatusWidget::setFeedRate(unsigned int feedRate) {
    ui->lineEditFeedRate->setText(QString::number(feedRate));
}

void StatusWidget::setSpindleSpeed(unsigned int spindleSpeed) {
    ui->lineEditSpindleSpeed->setText(QString::number(spindleSpeed));
}

void StatusWidget::setInputPinState(const InputPinState &inputPinState) {
    QStringList text;

    text << "X:" + QString::number(inputPinState.xLimit);
    text << "Y:" + QString::number(inputPinState.yLimit);
    text << "Z:" + QString::number(inputPinState.zLimit);
    text << "P:" + QString::number(inputPinState.probe);
    text << "D:" + QString::number(inputPinState.door);
    text << "H:" + QString::number(inputPinState.hold);
    text << "R:" + QString::number(inputPinState.softReset);
    text << "C:" + QString::number(inputPinState.cycleStart);

    ui->lineEditInputPinState->setText(text.join(" "));
}

void StatusWidget::setLineNumber(unsigned int lineNumber) {
    ui->lineEditLineNumber->setText(QString::number(lineNumber));
}

void StatusWidget::setMachineState(const MachineState &machineState) {

    QStringList text;

    switch (machineState.state) {
        case Idle:
            text << "Idle";
            break;
        case Run:
            text << "Run";
            break;
        case Hold:
            text << "Hold";
            break;
        case Jog:
            text << "Jog";
            break;
        case Alarm:
            text << "Alarm";
            break;;
        case Door:
            text << "Door";
            break;
        case Check:
            text << "Check";
            break;
        case Home:
            text << "Home";
            break;
        case Sleep:
            text << "Sleep";
            break;
    }

    if (machineState.code != -1) {
        text << QString::number(machineState.code);
    }

    ui->lineEditMachineState->setText(text.join(":"));
}

void StatusWidget::setOverriddenValues(const OverriddenValues &overriddenValues) {
    QStringList text;
    text << "S:" + QString::number(overriddenValues.spindle);
    text << "F:" + QString::number(overriddenValues.feed);
    text << "R:" + QString::number(overriddenValues.rapid);
    ui->lineEditOverridenValues->setText(text.join(" "));
}

void StatusWidget::setMachinePosition(const vec3 &machinePosition) {
    ui->widgetMPos->setValue(machinePosition);
}

void StatusWidget::setWorkPosition(const vec3 &workPosition) {
    ui->widgetWPos->setValue(workPosition);
}

void StatusWidget::setWorkCoordinateOffset(const vec3 &workCoordinateOffset) {
    ui->widgetWCO->setValue(workCoordinateOffset);
}


