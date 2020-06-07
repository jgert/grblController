//
// Created by Jakub Gert on 06/06/2020.
//

#ifndef GRBL_BUFFERSTATEPARSER_H
#define GRBL_BUFFERSTATEPARSER_H

#include <string>

using namespace std;

struct BufferState {
    unsigned int availableBlocks;
    unsigned int availableBytesInRxBuffer;
};

class BufferStateParser {
private:
    BufferState state;
public:
    bool parse(const string &status);
    BufferState getBufferState() const;
};


#endif //GRBL_BUFFERSTATEPARSER_H
