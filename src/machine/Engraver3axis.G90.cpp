//
// Created by Jakub Gert on 22/10/2020.
//
#include "Engraver3axis.h"

using namespace gCode;

bool Engraver3axis::parseG90(const gCode::Block &block) {

    if (block.chunks.size() != 1) {
        errors.emplace_back(block.lineNumber, Error::InvalidArgumentsCount);
        return false;
    }

    const auto& command = block.chunks[0];

    if (command.type != Chunk::Type::Command) {
        errors.emplace_back(block.lineNumber, Error::InvalidCommandChunkType);
        return false;
    }

    if (command.command != 90 || command.subcommand != 0) {
        errors.emplace_back(block.lineNumber, Error::InvalidCommandNumber);
        return false;
    }

    state.coordinateMode = State::Absolute;

    state.lastGCodeCommand = 90;
    state.lastGCodeSubcommand = 0;

    return true;
}
