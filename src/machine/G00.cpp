//
// Created by Jakub Gert on 22/10/2020.
//

#include "Parser.h"

namespace machine {

    bool G00(const gCode::Block &block, const MachineState &currentState, MachineState &nextState) {

        if (block.chunks.empty()) {
            nextState.error = Error(block.lineNumber, Error::MissingArguments);
            return false;
        }

        const auto &command = block.chunks[0];

        if (command.type != gCode::Chunk::Type::Command) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandChunkType);
            return false;
        }

        if (command.command != 0 || command.subcommand != 0) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandNumber);
            return false;
        }

        QVector3D offset;
        if (currentState.coordinateMode == MachineState::Absolute) {
            offset = currentState.currentPosition;
        }

        for (size_t a = 1; a < block.chunks.size(); a++) {
            const auto &chunk = block.chunks[a];

            if (chunk.type != gCode::Chunk::Type::Address) {
                nextState.error = Error(block.lineNumber, Error::UnexpectedChunkType);
                return false;
            }

            switch (chunk.address) {
                case 'X':
                    offset.setX(convertToMetricsIfNeeded(currentState, chunk.value));
                    break;
                case 'Y':
                    offset.setY(convertToMetricsIfNeeded(currentState, chunk.value));
                    break;
                case 'Z':
                    offset.setZ(convertToMetricsIfNeeded(currentState, chunk.value));
                    break;
                default:
                    nextState.error = Error(block.lineNumber, Error::InvalidAddress);
                    return false;
            }
        }

        switch (currentState.coordinateMode) {
            case MachineState::Absolute:
                nextState.operation = Operation(
                        OperationMove(
                                currentState.currentPosition,
                                offset,
                                -1));
                nextState.currentPosition = offset;
                break;
            case MachineState::Incremental:
                nextState.operation = Operation(
                        OperationMove(
                                currentState.currentPosition,
                                currentState.currentPosition + offset,
                                -1));
                nextState.currentPosition += offset;
                break;
        }

        nextState.lastGCodeCommand = command.command;
        nextState.lastGCodeSubcommand = command.subcommand;

        return true;
    }

}