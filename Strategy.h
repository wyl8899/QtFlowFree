#ifndef STRATEGY_H
#define STRATEGY_H

#include "Pipe.h"
#include "Board.h"

#include <QObject>
#include <QString>
#include <vector>

class Strategy : public QObject
{
    Q_OBJECT
public:
    explicit Strategy(int numOfColors, QObject *parent = 0) : QObject(parent) {
        pipes.resize(numOfColors);
        current = NoCurrentColor;
    }

    void paint() {
        for (auto &i : pipes) {
            if (i != nullptr)
                i->paint();
        }
    }

    inline int numOfColors() {
        return pipes.size();
    }

    QString inspect() {
        QStringList list;
        for (int i = 0; i < numOfColors(); ++i) {
            Pipe* pipe = pipes[i];
            QString pipeStr = pipe == nullptr ? QString("No pipe") : pipe->inspect();
            list << QString("[%1%2]%3").arg(i).arg(i==current?"*":"").arg(pipeStr);
        }
        return QString("Strategy: [%1]").arg(list.join(", "));
    }

    bool tryStartDraw(Point point) {
        if (tryStartDrawingAtStart(point))
            return true;
        if (tryStartDrawingAtMiddle(point))
            return true;
        // Not starting point nor occupied by existing pipes.
        // Fail.
        return false;
    }

    bool isTemporarilyOccupied(Point point) {
        if (isDrawing()) {
            return currentPipe()->contains(point);
        } else {
            return false;
        }
    }

    void startDraw(Point point) {
        if (tryStartDraw(point)) {
            paint();
        }
    }

    inline bool shouldExtend(Point point) {
        if (Board::isStart(point) && Board::getIndex(point) != current)
            return false;
        else
            return true;
    }

    void extendDraw(Point point) {
        if (shouldExtend(point)) {
            currentPipe()->extend(point);
            paint();
        }
    }

    void finishDraw() {
        if (!isDrawing())
            return;
        std::vector<Point>& currentPoints = currentPipe()->points();
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
    }

private:
    enum {
        NoCurrentColor = -1
    };

    std::vector<Pipe*> pipes;
    int current;

    bool isDrawing() {
        return current != NoCurrentColor;
    }

    Pipe* currentPipe() {
        assert(isDrawing());
        return pipes[current];
    }

    void startDrawAtStart(int color, Point point) {
        current = color;
        Pipe* &pipe = pipes[color];
        delete pipe;
        pipe = new Pipe(this, color, point, Board::getTheOther(color, point));
        pipe->setParent(this);
    }

    void startDrawAtMiddle(int color, Point point) {
        current = color;
        currentPipe()->start(point);
    }

    bool tryStartDrawingAtStart(Point point) {
        for (int i = 0; i < numOfColors(); ++i) {
            if (Board::isStart(point)) {
                startDrawAtStart(Board::getIndex(point), point);
                return true;
            }
        }
        return false;
    }

    bool tryStartDrawingAtMiddle(Point point) {
        for (int i = 0; i < numOfColors(); ++i) {
            Pipe* pipe = pipes[i];
            if (pipe != nullptr && pipe->contains(point)) {
                startDrawAtMiddle(i, point);
                return true;
            }
        }
        return false;
    }
};

#endif // STRATEGY_H
