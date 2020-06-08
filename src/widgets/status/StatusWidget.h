//
// Created by Jakub Gert on 07/06/2020.
//

#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <src/grbl/parsers/status_report/machine_state/MachineStateParser.h>
#include <src/grbl/parsers/status_report/overridden_values/OverriddenValuesParser.h>
#include <src/grbl/parsers/status_report/input_pin_state/InputPinStateParser.h>
#include "src/grbl/parsers/status_report/accessory_state/AccessoryStateParser.h"
#include "src/grbl/parsers/status_report/buffer_state/BufferStateParser.h"
#include "src/grbl/vec3/vec3.h"

namespace Ui {
    class StatusWidget;
}

class StatusWidget : public QWidget {
Q_OBJECT

public:
    explicit StatusWidget(QWidget *parent = nullptr);

    ~StatusWidget();

public slots:
    void setAccessoryState(AccessoryState state);

    void setBufferState(BufferState bufferState);

    void setFeedRate(unsigned int feedRate);

    void setSpindleSpeed(unsigned int spindleSpeed);

    void setInputPinState(const InputPinState &inputPinState);

    void setLineNumber(unsigned int lineNumber);

    void setMachineState(const MachineState &machineState);

    void setOverriddenValues(const OverriddenValues &overriddenValues);

    void setMachinePosition(const vec3 &machinePosition);

    void setWorkPosition(const vec3 &workPosition);

    void setWorkCoordinateOffset(const vec3 &workCoordinateOffset);

private:
    Ui::StatusWidget *ui;
};

#endif // STATUSWIDGET_H
