//
// Created by Jakub Gert on 23/10/2020.
//

#include "Engraver3axis.h"

using namespace gCode;

bool Engraver3axis::parseG20(const gCode::Block &block) {

    if (block.chunks.size() != 1) {
        errors.emplace_back(block.lineNumber, Error::InvalidArgumentsCount);
        return false;
    }

    const auto& command = block.chunks[0];

    if (command.type != Chunk::Type::Command) {
        errors.emplace_back(block.lineNumber, Error::InvalidCommandChunkType);
        return false;
    }

    if (command.command != 20 || command.subcommand != 0) {
        errors.emplace_back(block.lineNumber, Error::InvalidCommandNumber);
        return false;
    }

    state.units = State::Imperial;

    state.lastGCodeCommand = command.command;
    state.lastGCodeSubcommand = command.subcommand;

    return true;
}
