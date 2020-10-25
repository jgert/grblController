//
// Created by Jakub Gert on 22/10/2020.
//

#include "Engraver3axis.h"

Engraver3axis::Engraver3axis(State state): state(state) {

}

const vector<Error> &Engraver3axis::getErrors() const {
    return errors;
}

float Engraver3axis::convertToMetricsIfNeeded(float value) const {
    if (state.units == State::Imperial) {
        return value * 25.4f;
    } else {
        return value;
    }
}

const State &Engraver3axis::getState() const {
    return state;
}
