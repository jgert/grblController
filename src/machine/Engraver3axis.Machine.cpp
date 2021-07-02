//
// Created by Jakub Gert on 22/10/2020.
//
#include "Engraver3axis.h"
#include "Parser.h"

using namespace gCode;

namespace machine {

    void Engraver3axis::reset() {
        states.clear();
        states.emplace_back(initialState);
    }

    bool Engraver3axis::parse(const vector<gCode::Block> &blocks) {

        Engraver3axis::reset();

        bool result = true;
        for (const auto &block: blocks) {

            const MachineState &currentState = states.back();
            auto nextState = MachineState(currentState);
            nextState.error = Error();
            nextState.operation = Operation();

            result &= parseBlock(block, currentState, nextState);
            states.emplace_back(nextState);

            if (!result) {
                return false;
            }
        }

        return result;
    }

    const Error &Engraver3axis::error() const {
        return states.back().error;
    }

}
