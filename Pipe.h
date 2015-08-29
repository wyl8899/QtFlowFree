#ifndef PIPE_H
#define PIPE_H

#include "paint_common.h"
#include "Point.h"
#include "Grid.h"

#include <QObject>
#include <QString>
#include <QPoint>
#include <vector>

class Strategy;

class Pipe : public QObject {
    Q_OBJECT
public:
    Pipe(Strategy* _strategy, int _index, Point st, Point ed);

    QPointF getCenter(Point point);
    void paintLine(QPointF st, QPointF ed);
    void paintLines();
    void paintBackground(QRectF rect);
    void paintBackgrounds();
    void paint();
    QString inspect();

    const std::vector<Point>& points() {
        return path;
    }

    bool contains(Point point);
    bool isConnected();
    bool isTemporarilyOccupied(Point point);
    void start(Point point);
    void extend(Point point);
    void intercept(Point point);
    void finish();

private:
    enum {
        PointNotFound = -1
    };

    enum State {
        NotDrawing,
        Drawing
    };

    int index;
    Point dest;
    std::vector<Point> path;
    State state;
    Strategy* strategy;
    ItemList* itemList;

    int getIndex(Point point);
};

#endif // PIPE_H

