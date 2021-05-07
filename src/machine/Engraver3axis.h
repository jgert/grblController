//
// Created by Jakub Gert on 22/10/2020.
//

#ifndef GRBL_ENGRAVER3AXIS_H
#define GRBL_ENGRAVER3AXIS_H

#include <QVector3D>
#include "Parser.h"
#include "Machine.h"

namespace machine {

    class Engraver3axis : public Machine {
    private:
        bool parseBlock(const gCode::Block &block, const MachineState &currentState, MachineState &nextState);

    public:

        explicit Engraver3axis(const MachineState &state = MachineState());

        void reset() override;

        bool parse(const vector<gCode::Block> &blocks) override;

    };

}

#endif //GRBL_ENGRAVER3AXIS_H
