//
// Created by Jakub Gert on 22/10/2020.
//
#include "Engraver3axis.h"

using namespace gCode;

void Engraver3axis::reset() {
    Machine::reset();
    state = State();
    errors.clear();
}

bool Engraver3axis::parse(const vector<gCode::Block> &blocks) {

    Engraver3axis::reset();

    bool result = true;
    for (const auto &block: blocks) {

        result &= parseBlock(block);

        if (!result) {
            errors.emplace_back(block.lineNumber, Error::NotSupported);
        }
        if (!result) {
            return false;
        }
    }

    return result;
}

bool Engraver3axis::parseBlock(const gCode::Block &block) {

    if (block.chunks.empty()) {
        return true;
    }

    const auto chunk = block.chunks[0];

    state.sourceLineNumber = block.lineNumber;

    switch (chunk.type) {
        case Chunk::Type::Error:
            return false;
        case Chunk::Type::Percent:
            return true;
        case Chunk::Type::LineNumber:
            state.programLineNumber = chunk.programLineNumber;
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
                    return parseG00(block);
                case 1:
                    return parseG01(block);
                case 17:
                    return parseG17(block);
                case 18:
                    return parseG18(block);
                case 19:
                    return parseG19(block);
                case 20:
                    return parseG20(block);
                case 21:
                    return parseG21(block);
                case 90:
                    return parseG90(block);
                case 91:
                    return parseG91(block);
                default:
                    return false;
            }
        default:
            return false;
    }
}
