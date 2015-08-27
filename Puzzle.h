#ifndef PUZZLE_H
#define PUZZLE_H

#include "GameConfig.h"
#include "Board.h"
#include "Strategy.h"
#include "Point.h"

#include <QObject>
#include <QString>

class Puzzle : public QObject {
    Q_OBJECT
public:
    Puzzle(GameConfig config, QObject* parent = 0) : QObject(parent) {
        board = new Board(config, this);
        strategy = new Strategy(config.numOfColors(), this);
    }

    QString inspect() {
        return QString("Puzzle: [%1]").arg(strategy->inspect());
    }

    void startDraw(Point point) {
        strategy->startDraw(point);
    }
    void extendDraw(Point point) {
        strategy->extendDraw(point);
    }
    void finishDraw() {
        strategy->finishDraw();
    }

private:
    Board* board;
    Strategy* strategy;
};

#endif // PUZZLE_H
