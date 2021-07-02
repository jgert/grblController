//
// Created by Jakub Gert on 22/10/2020.
//

#include "Parser.h"

using namespace gCode;

namespace machine {

    bool G91(const gCode::Block &block, MachineState &nextState) {

        if (block.chunks.size() != 1) {
            nextState.error = Error(block.lineNumber, Error::InvalidArgumentsCount);
            return false;
        }

        const auto &command = block.chunks[0];

        if (command.type != Chunk::Type::Command) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandChunkType);
            return false;
        }

        if (command.command != 91 || command.subcommand != 0) {
            nextState.error = Error(block.lineNumber, Error::InvalidCommandNumber);
            return false;
        }

        nextState.coordinateMode = MachineState::Incremental;

        nextState.lastGCodeCommand = 91;
        nextState.lastGCodeSubcommand = 0;

        return true;
    }

}
