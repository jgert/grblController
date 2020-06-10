//
// Created by Jakub Gert on 01/06/2020.
//

#ifndef GRBL_GRBL_H
#define GRBL_GRBL_H

#include <QObject>
#include <QString>
#include <QVector3D>

#include "src/grbl/parsers/alarm/AlarmParser.h"
#include "src/grbl/parsers/status_report/accessory_state/AccessoryStateParser.h"
#include "src/grbl/parsers/status_report/buffer_state/BufferStateParser.h"
#include "src/grbl/parsers/status_report/feed_rate/FeedRateParser.h"
#include "src/grbl/parsers/status_report/feed_rate_spindle_speed/FeedRateAndSpindleSpeedParser.h"
#include "src/grbl/parsers/status_report/input_pin_state/InputPinStateParser.h"
#include "src/grbl/parsers/status_report/line_number/LineNumberParser.h"
#include "src/grbl/parsers/status_report/machine_state/MachineStateParser.h"
#include "src/grbl/parsers/status_report/overridden_values/OverriddenValuesParser.h"
#include "src/grbl/parsers/status_report/position_parser/PositionParser.h"
#include "src/grbl/parsers/welcome_message/WelcomeMessageParser.h"

class GRBL : public QObject {
Q_OBJECT
private:
    AlarmParser alarmParser;
    AccessoryStateParser accessoryStateParser;
    BufferStateParser bufferStateParser;
    FeedRateParser feedRateParser;
    FeedRateAndSpindleSpeedParser feedRateAndSpindleSpeedParser;
    InputPinStateParser inputPinStateParser;
    LineNumberParser lineNumberParser;
    MachineStateParser machineStateParser;
    OverriddenValuesParser overriddenValuesParser;
    PositionParser positionParser;
    WelcomeMessageParser welcomeMessageParser;

    AccessoryState accessoryState;
public:
    QStringList error;
private:
    
    bool parseStatus(const QString &message);
    bool parseWelcomeMessage(const QString &message);

public:

    void parse(const QByteArray &data);

signals:

    void onReceivedAlarm(unsigned int code);

    void onReceivedAccessoryState(AccessoryState state);

    void onReceivedBufferState(BufferState state);

    void onReceivedFeedRate(unsigned int feedRate);

    void onReceivedSpindleSpeed(unsigned int spindleSpeed);

    void onReceivedInputPinState(InputPinState inputPinState);

    void onReceivedLineNumber(unsigned int lineNumber);

    void onReceivedMachineState(MachineState state);

    void onReceivedOverriddenValues(OverriddenValues overriddenValues);

    void onReceivedMPos(const vec3 &position);

    void onReceivedWPos(const vec3 &position);

    void onReceivedWorkCoordinateOffset(const vec3 &position);

    void onReceivedWelcomeMessage(const QString &message);

    void onParserError(const QString &message);

};


#endif //GRBL_GRBL_H
