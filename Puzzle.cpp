#include "Puzzle.h"

Puzzle::Puzzle(GameConfig config, QObject *parent) : QObject(parent) {
    board = new Board(config, this);
    strategy = new Strategy(config.numOfColors(), this);
}

Puzzle::~Puzzle() {
}

QString Puzzle::inspect() {
    return QString("Puzzle: [%1]").arg(strategy->inspect());
}

void Puzzle::startDraw(Point point) {
    strategy->startDraw(point);
}

void Puzzle::extendDraw(Point point) {
    strategy->extendDraw(point);
}

void Puzzle::finishDraw() {
    strategy->finishDraw();
}
