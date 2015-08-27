#ifndef PUZZLE_H
#define PUZZLE_H

#include "GameConfig.h"
#include "Board.h"
#include "Strategy.h"
#include "Point.h"

#include <QObject>
#include <QString>
#include <QDebug>
#include <cassert>

class Puzzle : public QObject {
    Q_OBJECT
public:
    Puzzle(GameConfig config, QObject* parent = 0) : QObject(parent) {
        singleton = this;
        board = new Board(config, this);
        strategy = new Strategy(config.numOfColors(), this);
    }

    ~Puzzle() {
        singleton = nullptr;
    }

    QString inspect() {
        return QString("Puzzle: [%1]").arg(strategy->inspect());
    }

    static Puzzle* instance() {
        assert(singleton != nullptr);
        return singleton;
    }

    static void startDraw(Point point) {
        instance()->_startDraw(point);
    }

    static void extendDraw(Point point) {
        instance()->_extendDraw(point);
    }

    static void finishDraw() {
        instance()->_finishDraw();
    }

    void _startDraw(Point point) {
        strategy->startDraw(point);
    }
    void _extendDraw(Point point) {
        strategy->extendDraw(point);
    }
    void _finishDraw() {
        strategy->finishDraw();
    }

private:
    static Puzzle* singleton;

    Board* board;
    Strategy* strategy;
};

#endif // PUZZLE_H
