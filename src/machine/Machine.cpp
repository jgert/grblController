//
// Created by Jakub Gert on 23/10/2020.
//

#include "Machine.h"

namespace machine {

#define G(C, S) C*100+S

    Machine::ModalGroup Machine::modalGroup(
            unsigned int command,
            unsigned int subcommand) {


        unsigned int type = command * 100 + subcommand;

        switch (type) {
            case G(4, 0):
            case G(10, 0):
            case G(28, 0):
            case G(30, 0):
            case G(52, 0):
            case G(53, 0):
            case G(92, 0):
            case G(92, 1):
            case G(92, 2):
            case G(92, 3):
                return ModalGroup::NonModalCode;
            case G(0, 0):
            case G(1, 0):
            case G(2, 0):
            case G(3, 0):
            case G(33, 0):
            case G(38, 2):
            case G(38, 3):
            case G(38, 4):
            case G(38, 5):
            case G(73, 0):
            case G(76, 0):
            case G(80, 0):
            case G(81, 0):
            case G(82, 0):
            case G(83, 0):
            case G(84, 0):
            case G(85, 0):
            case G(86, 0):
            case G(87, 0):
            case G(88, 0):
            case G(89, 0):
                return ModalGroup::Motion;
            case G(17, 0):
            case G(18, 0):
            case G(19, 0):
            case G(17, 1):
            case G(18, 1):
            case G(19, 1):
                return ModalGroup::PlaneSelection;
            case G(90, 0):
            case G(91, 0):
                return ModalGroup::DistanceMode;
            case G(93, 0):
            case G(94, 0):
            case G(95, 0):
                return ModalGroup::FeedRateMode;
            case G(20, 0):
            case G(21, 0):
                return ModalGroup::Units;
            case G(40, 0):
            case G(41, 0):
            case G(42, 0):
            case G(41, 1):
            case G(42, 1):
                return ModalGroup::CutterDiameterCompensation;
            case G(43, 0):
            case G(43, 1):
            case G(49, 0):
                return ModalGroup::ToolLengthOffset;
            case G(98, 0):
            case G(99, 0):
                return ModalGroup::CannedCyclesReturnMode;
            case G(54, 0):
            case G(55, 0):
            case G(56, 0):
            case G(57, 0):
            case G(58, 0):
            case G(59, 0):
            case G(59, 1):
            case G(59, 2):
            case G(59, 3):
                return ModalGroup::CoordinateSystem;
            case G(61, 0):
            case G(61, 1):
            case G(64, 0):
                return ModalGroup::ControlMode;
            case G(96, 0):
            case G(97, 0):
                return ModalGroup::SpindleSpeedMode;
            case G(7, 0):
            case G(8, 0):
                return ModalGroup::LatheDiameterMode;
            default:
                return ModalGroup::Unknown;

        }
    }

    Machine::Machine(const MachineState &initialState) : initialState(initialState) {

    }

    const vector<MachineState> &Machine::getStates() const {
        return states;
    }

#undef G

}
