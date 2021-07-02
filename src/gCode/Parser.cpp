//
// Created by Jakub Gert on 28/09/2020.
//

#include <string>
#include <regex>
#include <sstream>
#include "Parser.h"
#include "split.h"

using namespace std;
namespace gCode {

    bool Parser::parse(const std::string &line) {

        parsed_blocks.clear();

        auto lines = splitByNewLine(line);

        parsed_blocks.reserve(lines.size()*2);

        LineNumber_t lineNumber = 0;

        for(const auto& item: lines) {
            Block block;
            block.lineNumber = lineNumber;

            auto start = item.begin();
            auto begin = item.begin();
            auto end = item.end();

            while (begin != end) {
                Chunk chunk;
                chunk.startPosition = distance(start, begin);

                if (*begin == ' ' || *begin == '\t') {
                    begin += 1;
                    continue;
                }

                auto sourceLine = string(begin, end);
                auto currentLine = string(begin, end);
                std::transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::toupper);
                std::smatch cm;

                static regex regexPercent("^%$");
                if (regex_match(currentLine, cm, regexPercent)) {
                    chunk.type = Chunk::Type::Percent;
                    chunk.comment = item;
                    chunk.length = cm.length();
                    block.chunks.push_back(chunk);
                    parsed_blocks.push_back(block);
                    return true;
                }

                static regex regexComment(R"(^\(.*\)|^;.*|^\[.*\])");
                if (regex_search(sourceLine, cm, regexComment)) {
                    chunk.type = Chunk::Comment;
                    chunk.length = cm.length();
                    chunk.comment = cm.str();
                    block.chunks.push_back(chunk);
                    begin += cm.length(0);
                    continue;
                }

                static regex regexLineNumber(R"(^[N]([0-9]+))");
                if (regex_search(currentLine, cm, regexLineNumber)) {
                    chunk.type = Chunk::LineNumber;
                    chunk.hasProgramLineNumber = true;
                    chunk.programLineNumber = stoi(cm[1].str());
                    chunk.length = cm.length();
                    block.chunks.push_back(chunk);
                    begin += cm.length(0);
                    continue;
                }

                static regex regexCommandExtended(R"(^[G](\d+)\.(\d))");
                if (regex_search(currentLine, cm, regexCommandExtended)) {
                    chunk.type = Chunk::Command;
                    chunk.length = cm.length();
                    chunk.command = stoi(cm[1].str());
                    chunk.subcommand = stoi(cm[2].str());
                    block.chunks.push_back(chunk);
                    begin += cm.length(0);
                    continue;
                }

                static regex regexCommand(R"(^[G](\d+))");
                if (regex_search(currentLine, cm, regexCommand)) {
                    chunk.type = Chunk::Command;
                    chunk.length = cm.length();
                    chunk.command = stoi(cm[1].str());
                    block.chunks.push_back(chunk);
                    begin += cm.length(0);
                    continue;
                }

                static regex regexM(R"(^[M](\d+))");
                if (regex_search(currentLine, cm, regexM)) {
                    chunk.type = Chunk::M;
                    chunk.command = stoi(cm[1].str());
                    chunk.length = cm.length();
                    block.chunks.push_back(chunk);
                    begin += cm.length(0);
                    continue;
                }

                static regex regexT(R"(^[T](\d+))");
                if (regex_search(currentLine, cm, regexT)) {
                    chunk.type = Chunk::Tool;
                    chunk.command = stoi(cm[1].str());
                    chunk.length = cm.length();
                    block.chunks.push_back(chunk);
                    begin += cm.length(0);
                    continue;
                }

                // https://github.com/gnea/grbl/blob/master/grbl/gcode.c
                static regex regexAddress(R"(^([FIJKLNPRSTXYZ])\s*([+-]?\d*([.]?\d+|\.)))");
                if (regex_search(currentLine, cm, regexAddress)) {
                    chunk.type = Chunk::Address;
                    chunk.length = cm.length();
                    chunk.address = cm[1].str()[0];
                    chunk.value = stof(cm[2].str());
                    block.chunks.push_back(chunk);
                    begin += cm.length(0);
                    continue;
                }

                chunk.type = Chunk::Error;
                chunk.comment = sourceLine;
                chunk.length = sourceLine.length();
                block.chunks.push_back(chunk);
                parsed_blocks.push_back(block);
                return false;
            }

            parsed_blocks.push_back(block);
            lineNumber += 1;
        }

        return true;
    }

    const vector<Block> &Parser::blocks() const{
        return parsed_blocks;
    }
}
