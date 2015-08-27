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

    void startDraw(Point point) {
        if (tryAtStart(point))
            return;
        if (tryAtMiddle(point))
            return;
        // Not starting point nor occupied by existing pipes.
        // Fail.
    }

    void extendDraw(Point point) {
        Pipe* pipe = pipes[current];
        pipe->extend(point);
    }

    void finishDraw() {
        Pipe* currentPipe = pipes[current];
        std::vector<Point>& currentPoints = currentPipe->points();
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

    void startDrawAtStart(int color, Point point) {
        current = color;
        Pipe* &pipe = pipes[color];
        delete pipe;
        pipe = new Pipe(this, point, Board::getTheOther(color, point));
    }

    void startDrawAtMiddle(int color, Point point) {
        current = color;
        Pipe* pipe = pipes[color];
        pipe->extend(point);
    }

    bool tryAtStart(Point point) {
        for (int i = 0; i < numOfColors(); ++i) {
            if (Board::isStart(point)) {
                startDrawAtStart(Board::getIndex(point), point);
                return true;
            }
        }
        return false;
    }

    bool tryAtMiddle(Point point) {
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
