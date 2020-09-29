//
// Created by Jakub Gert on 28/09/2020.
//

#ifndef GRBL_PARSER_H
#define GRBL_PARSER_H

#include <iostream>
#include <vector>

using namespace std;

namespace gCode {

    struct Chunk {
        typedef enum {
            Percent,
            Command,
            LineNumber,
            M,
            Address,
            Tool
        } Type;

        Chunk::Type type;
        string comment;
        bool hasLineNumber = false;
        uint32_t lineNumber = 0;
        uint8_t command = 0;
        bool hasSubcommand = false;
        uint8_t subcommand = false;
        char address;
        float value = 0;
    };

    class Parser {
        vector<Chunk> parsedChunks;
        Chunk current;
        string error;
    public:
        bool parse(const string &line);

        const vector<Chunk> &chunks();
    };
}
#endif //GRBL_PARSER_H
