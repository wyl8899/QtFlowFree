#ifndef PUZZLE_H
#define PUZZLE_H

#include "common.h"
#include "GameConfig.h"
#include "Board.h"
#include "Strategy.h"
#include "Point.h"

#include <QObject>
#include <QString>
#include <QDebug>
#include <cassert>

class Puzzle : public QObject, private LocatorRegister<Puzzle> {
    Q_OBJECT
public:
    Puzzle(GameConfig config, QObject* parent = 0);
    ~Puzzle();

    QString inspect();

    void startDraw(Point point);
    void extendDraw(Point point);
    void finishDraw();
private:
    Board* board;
    Strategy* strategy;
};

#endif // PUZZLE_H
