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
    explicit Strategy(int numOfColors, QObject *parent = 0);

    void paint();

    inline int numOfColors() {
        return pipes.size();
    }

    QString inspect();

    bool isTemporarilyOccupied(Point point);

    void startDraw(Point point);
    void extendDraw(Point point);
    void finishDraw();

private:
    enum {
        NoCurrentColor = -1
    };

    std::vector<Pipe*> pipes;
    int current;

    inline bool isDrawing() {
        return current != NoCurrentColor;
    }

    inline Pipe* currentPipe() {
        assert(isDrawing());
        return pipes[current];
    }

    bool tryStartDraw(Point point);
    bool shouldExtend(Point point);
    void startDrawAtStart(int color, Point point);
    void startDrawAtMiddle(int color, Point point);
    bool tryStartDrawingAtStart(Point point);
    bool tryStartDrawingAtMiddle(Point point);
};

#endif // STRATEGY_H
