//
// Created by Jakub Gert on 22/10/2020.
//

#include "Engraver3axis.h"

using namespace gCode;

namespace machine {

    Engraver3axis::Engraver3axis(const MachineState &initialState) : Machine(initialState) {

    }

    bool
    Engraver3axis::parseBlock(const gCode::Block &block, const MachineState &currentState, MachineState &nextState) {

        if (block.chunks.empty()) {
            return true;
        }

        const auto chunk = block.chunks[0];

        nextState.sourceLineNumber = block.lineNumber;

        switch (chunk.type) {
            case Chunk::Type::Error:
                return false;
            case Chunk::Type::Percent:
                return true;
            case Chunk::Type::LineNumber:
                nextState.programLineNumber = chunk.programLineNumber;
                return true;
            case Chunk::Type::M:
                return false;
            case Chunk::Type::Comment:
                return true;
            case Chunk::Type::Address:
                return false;
            case Chunk::Type::Tool:
                return false;
            case Chunk::Type::Command:
                switch (chunk.command) {
                    case 0:
                        return G00(block, currentState, nextState);
                    case 1:
                        return G01(block, currentState, nextState);
                    case 2:
                    case 3:
                        return G02_G03(block, currentState, nextState);
                    case 17:
                        return G17(block, nextState);
                    case 18:
                        return G18(block, nextState);
                    case 19:
                        return G19(block, nextState);
                    case 20:
                        return G20(block, nextState);
                    case 21:
                        return G21(block, nextState);
                    case 90:
                        return G90(block, nextState);
                    case 91:
                        return G91(block, nextState);
                    default:
                        return false;
                }
            default:
                return false;
        }
    }

}
