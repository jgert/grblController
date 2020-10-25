//
// Created by Jakub Gert on 23/10/2020.
//
#include "Engraver3axis.h"

using namespace gCode;

bool Engraver3axis::parseG01(const gCode::Block &block) {

    if (block.chunks.empty()) {
        errors.emplace_back(block.lineNumber, Error::MissingArguments);
        return false;
    }

    const auto& command = block.chunks[0];

    if (command.type != Chunk::Type::Command) {
        errors.emplace_back(block.lineNumber, Error::InvalidCommandChunkType);
        return false;
    }

    if (command.command != 1 || command.subcommand != 0) {
        errors.emplace_back(block.lineNumber, Error::InvalidCommandNumber);
        return false;
    }

    QVector3D offset;
    if (state.coordinateMode == State::Absolute) {
        offset = state.currentPosition;
    }

    for (size_t a = 1; a < block.chunks.size(); a++) {
        const auto &chunk = block.chunks[a];

        if (chunk.type != Chunk::Type::Address) {
            errors.emplace_back(block.lineNumber, Error::UnexpectedChunkType);
            return false;
        }

        switch (chunk.address) {
            case 'X':
                offset.setX(convertToMetricsIfNeeded(chunk.value));
                break;
            case 'Y':
                offset.setY(convertToMetricsIfNeeded(chunk.value));
                break;
            case 'Z':
                offset.setZ(convertToMetricsIfNeeded(chunk.value));
                break;
            case 'F':
                state.feedRate = chunk.value;
                break;
            default:
                errors.emplace_back(block.lineNumber, Error::InvalidAddress);
                return false;
        }
    }

    switch (state.coordinateMode) {
        case State::Absolute:
            operations.emplace_back(
                    OperationMove(
                            state.currentPosition,
                            offset,
                            -1));
            state.currentPosition = offset;
            break;
        case State::Incremental:
            operations.emplace_back(
                    OperationMove(
                            state.currentPosition,
                            state.currentPosition + offset,
                            -1));
            state.currentPosition += offset;
            break;
    }

    state.lastGCodeCommand = command.command;
    state.lastGCodeSubcommand = command.subcommand;

    return true;
}
