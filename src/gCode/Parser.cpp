//
// Created by Jakub Gert on 28/09/2020.
//

#include <string>
#include <regex>
#include "Parser.h"

using namespace std;
namespace gCode {

    bool Parser::parse(const std::string &line) {
        Chunk chunk;

        auto begin = line.begin();
        auto end = line.end();

        while (begin != end) {

            if (*begin == ' ') {
                begin += 1;
                continue;
            }

            static regex regexPercent("^%$");

            auto currentLine = string(begin, end);
            std::transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::toupper);
            std::smatch cm;

            if (regex_match(currentLine, cm, regexPercent)) {
                chunk.type = Chunk::Type::Percent;
                chunk.comment = line;
                parsedChunks.push_back(chunk);
                return true;
            }

            static regex regexLineNumber(R"(^[N]([0-9]+))");
            if (regex_search(currentLine, cm, regexLineNumber)) {
                chunk.type = Chunk::LineNumber;
                chunk.hasLineNumber = true;
                chunk.lineNumber = stoi(cm[1].str());
                parsedChunks.push_back(chunk);
                begin += cm.length(0);
                continue;
            }

            static regex regexCommandExtended(R"(^[G](\d+)\.(\d))");
            if (regex_search(currentLine, cm, regexCommandExtended)) {
                chunk.type = Chunk::Command;
                chunk.hasSubcommand = true;
                chunk.command = stoi(cm[1].str());
                chunk.subcommand = stoi(cm[2].str());
                parsedChunks.push_back(chunk);
                begin += cm.length(0);
                continue;
            }

            static regex regexCommand(R"(^[G](\d+))");
            if (regex_search(currentLine, cm, regexCommand)) {
                chunk.type = Chunk::Command;
                chunk.command = stoi(cm[1].str());
                parsedChunks.push_back(chunk);
                begin += cm.length(0);
                continue;
            }

            static regex regexM(R"(^[M](\d+))");
            if (regex_search(currentLine, cm, regexM)) {
                chunk.type = Chunk::M;
                chunk.command = stoi(cm[1].str());
                parsedChunks.push_back(chunk);
                begin += cm.length(0);
                continue;
            }

            static regex regexT(R"(^[T](\d+))");
            if (regex_search(currentLine, cm, regexT)) {
                chunk.type = Chunk::Tool;
                chunk.command = stoi(cm[1].str());
                parsedChunks.push_back(chunk);
                begin += cm.length(0);
                continue;
            }

            static regex regexAddress(R"(^([^GM])\s*([+-]?\d*[.]?\d+))");
            if (regex_search(currentLine, cm, regexAddress)) {
                chunk.type = Chunk::Address;
                chunk.address = cm[1].str()[0];
                chunk.value = stof(cm[2].str());
                parsedChunks.push_back(chunk);
                begin += cm.length(0);
                continue;
            }
            return false;
        }

        return true;
    }

    const vector<Chunk> &Parser::chunks() {
        return parsedChunks;
    }
}
