//
// Created by Jakub Gert on 01/06/2020.
//

#include <QRegExp>
#include <QRegularExpression>
#include <QDebug>
#include "GRBL.h"

MachineState::MachineState(State state, Code code) : state(state), code(code) {}

MachineState::MachineState() : state(State::Idle), code(-1) {}

void GRBL::parse(const QByteArray &data) {

    QString message(data);

    if(data.isEmpty()) {
        return;
    }

    if (parseStatus(message)) {
        return;
    } else if (alarmParser.parse(message.toStdString())) {
        emit onReceivedAlarm(alarmParser.getAlarmValue());
        return;
    } else if (parseWelcomeMessage(message)) {
        return;
    } else {
        emit onParserError("Unsupported message: >>" + message + "<<");
    }
}

bool GRBL::parseWelcomeMessage(const QString &message) {

    if (!welcomeMessageParser.parse(message.toStdString())) {
        return false;
    }

    auto version = QString(welcomeMessageParser.getVersion().c_str());
    emit onReceivedWelcomeMessage(version);

    return true;
}

bool GRBL::parseStatus(const QString &message) {

    QRegExp regexStatus("<{1}(.*)>{1}");

    if (!regexStatus.exactMatch(message)) {
        return false;
    }

    auto statusMessage = regexStatus.cap(1);

    QStringList list = statusMessage.split("|");

    QStringListIterator iterator(list);

    bool result = true;

    while (iterator.hasNext() && result) {
        const string status = QString(iterator.next()).toStdString();
        if (accessoryStateParser.parse(status)) {
            AccessoryState current = accessoryStateParser.getAccessoryState();
            if (!(current == accessoryState)) {
                accessoryState = current;
                emit onReceivedAccessoryState(current);
            }
        } else if (bufferStateParser.parse(status)) {
            emit onReceivedBufferState(bufferStateParser.getBufferState());
        } else if (feedRateParser.parse(status)) {
            emit onReceivedFeedRate(feedRateParser.getFeedRate());
            emit onReceivedSpindleSpeed(0);
        } else if (feedRateAndSpindleSpeedParser.parse(status)) {
            emit onReceivedFeedRate(feedRateAndSpindleSpeedParser.getFeedRate());
            emit onReceivedSpindleSpeed(feedRateAndSpindleSpeedParser.getSpindleSpeed());
        } else if (inputPinStateParser.parse(status)) {
            emit onReceivedInputPinState(inputPinStateParser.getInputPinState());
        } else if (lineNumberParser.parse(status)) {
            emit onReceivedLineNumber(lineNumberParser.getLineNumber());
        } else if (machineStateParser.parse(status)) {
            emit onReceivedMachineState(machineStateParser.getMachineState());
        } else if (overriddenValuesParser.parse(status)) {
            emit onReceivedOverriddenValues(overriddenValuesParser.getOverriddenValues());
        } else if (positionParser.parse(status)) {
            emit onReceivedMPos(positionParser.getMachinePosition());
            emit onReceivedWPos(positionParser.getWorkPosition());
            emit onReceivedWorkCoordinateOffset(positionParser.getWorkCoordinateOffset());
        } else {
            result = false;
        }
    }

    return result;
}
