#include "Strategy.h"


Strategy::Strategy(int numOfColors, QObject *parent) : QObject(parent) {
    pipes.resize(numOfColors);
    current = NoCurrentColor;
}

void Strategy::paint() {
    for (auto &i : pipes) {
        if (i != nullptr)
            i->paint();
    }
}

QString Strategy::inspect() {
    QStringList list;
    for (int i = 0; i < numOfColors(); ++i) {
        Pipe* pipe = pipes[i];
        QString pipeStr = pipe == nullptr ? QString("No pipe") : pipe->inspect();
        list << QString("[%1%2]%3").arg(i).arg(i==current?"*":"").arg(pipeStr);
    }
    return QString("Strategy: [%1]").arg(list.join(", "));
}

bool Strategy::tryStartDraw(Point point) {
    if (tryStartDrawingAtStart(point))
        return true;
    if (tryStartDrawingAtMiddle(point))
        return true;
    // Not starting point nor occupied by existing pipes.
    // Fail.
    return false;
}

bool Strategy::isTemporarilyOccupied(Point point) {
    if (isDrawing()) {
        return currentPipe()->contains(point);
    } else {
        return false;
    }
}

void Strategy::startDraw(Point point) {
    if (tryStartDraw(point)) {
        paint();
    }
}

bool Strategy::shouldExtend(Point point) {
    if (Board::isStart(point) && Board::getIndex(point) != current)
        return false;
    else
        return true;
}

void Strategy::extendDraw(Point point) {
    if (isDrawing() && shouldExtend(point)) {
        currentPipe()->extend(point);
        paint();
    }
}

void Strategy::finishDraw() {
    if (!isDrawing())
        return;
    const std::vector<Point>& currentPoints = currentPipe()->points();
    currentPipe()->finish();
    for (auto point : currentPoints) {
        for (int i = 0; i < numOfColors(); ++i)
            if (i != current) {
                Pipe* pipe = pipes[i];
                if (pipe != nullptr)
                    pipe->intercept(point);
            }
    }
    current = NoCurrentColor;
    paint();
}

void Strategy::startDrawAtStart(int color, Point point) {
    current = color;
    Pipe* &pipe = pipes[color];
    delete pipe;
    pipe = new Pipe(this, color, point, Board::getTheOther(color, point));
    pipe->setParent(this);
}

void Strategy::startDrawAtMiddle(int color, Point point) {
    current = color;
    currentPipe()->start(point);
}

bool Strategy::tryStartDrawingAtStart(Point point) {
    for (int i = 0; i < numOfColors(); ++i) {
        if (Board::isStart(point)) {
            startDrawAtStart(Board::getIndex(point), point);
            return true;
        }
    }
    return false;
}

bool Strategy::tryStartDrawingAtMiddle(Point point) {
    for (int i = 0; i < numOfColors(); ++i) {
        Pipe* pipe = pipes[i];
        if (pipe != nullptr && pipe->contains(point)) {
            startDrawAtMiddle(i, point);
            return true;
        }
    }
    return false;
}
