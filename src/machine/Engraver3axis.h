//
// Created by Jakub Gert on 22/10/2020.
//

#ifndef GRBL_ENGRAVER3AXIS_H
#define GRBL_ENGRAVER3AXIS_H

#include <QVector3D>
#include "Machine.h"

struct State {
    typedef enum {
        Absolute,
        Incremental
    } CoordinateMode;
    typedef enum {
        Imperial,
        Metric,
    } Units;
    typedef enum {
        XY,
        ZX,
        YZ
    }PlaneSelection;
    Units units;
    QVector3D currentPosition;
    QVector3D startingPosition;
    CoordinateMode coordinateMode;
    PlaneSelection planeSelection;
    float feedRate;
    unsigned int programLineNumber;
    unsigned int sourceLineNumber;
    unsigned int lastGCodeCommand;
    unsigned int lastGCodeSubcommand;


    State() :
            units(Metric),
            currentPosition(QVector3D(0, 0, 0)),
            startingPosition(QVector3D(0, 0, 0)),
            coordinateMode(CoordinateMode::Absolute),
            planeSelection(PlaneSelection::XY),
            feedRate(-1),
            programLineNumber(0),
            sourceLineNumber(0),
            lastGCodeCommand(0),
            lastGCodeSubcommand(0) {
    }
};

class Engraver3axis : public Machine {
private:
    State state;

    float convertToMetricsIfNeeded(float value) const;
    unsigned int modalGroup(unsigned int command);
    unsigned int modalGroup(unsigned int command, unsigned int subcommand);
public:

    Engraver3axis(State state = State());

    void reset() override;

    const State &getState() const;

    bool parse(const vector<gCode::Block> &blocks) override;

    bool parseBlock(const gCode::Block &block);

    bool parseG00(const gCode::Block &block);

    bool parseG01(const gCode::Block &block);

    bool parseG17(const gCode::Block &block);

    bool parseG18(const gCode::Block &block);

    bool parseG19(const gCode::Block &block);

    bool parseG20(const gCode::Block &block);

    bool parseG21(const gCode::Block &block);

    bool parseG90(const gCode::Block &block);

    bool parseG91(const gCode::Block &block);
};


#endif //GRBL_ENGRAVER3AXIS_H
