//
// Created by Jakub Gert on 28/09/2020.
//

#ifndef GRBL_GCODEPARSER_H
#define GRBL_GCODEPARSER_H

#include <iostream>
#include <vector>

namespace gCode {

    typedef uint32_t LineNumber_t;

    struct Chunk {
        typedef enum {
            Error,
            Percent,
            Command,
            LineNumber,
            M,
            Address,
            Tool,
            Comment,
        } Type;

        Chunk::Type type;
        std::string comment;
        bool hasProgramLineNumber = false;
        LineNumber_t programLineNumber = 0;
        uint8_t command = 0;
        uint8_t subcommand = 0;
        char address;
        float value = 0;
        LineNumber_t startPosition = 0;
        LineNumber_t length = 0;
    };

    struct Block {
        LineNumber_t lineNumber = 0;
        std::vector<Chunk> chunks;
    };

    class Parser {
        std::vector<Block> parsed_blocks;
    public:
        bool parse(const std::string &line);

        [[nodiscard]] const std::vector<Block>& blocks() const;
    };
}
#endif //GRBL_GCODEPARSER_H
