//
// Created by Jakub Gert on 23/10/2020.
//

#include "Parser.h"

using namespace gCode;

namespace machine {

    bool G21(const gCode::Block &block, MachineState &nextState) {

        if (block.chunks.size() != 1) {
            nextState.error = Error(block.lineNumber, Error::InvalidArgumentsCount);
            return false;
        }

        const auto &command = block.chunks[0];

        if (command.type != Chunk::Type::Command) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandChunkType);
            return false;
        }

        if (command.command != 21 || command.subcommand != 0) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandNumber);
            return false;
        }

        nextState.units = MachineState::Metric;

        nextState.lastGCodeCommand = command.command;
        nextState.lastGCodeSubcommand = command.subcommand;

        return true;
    }

}
