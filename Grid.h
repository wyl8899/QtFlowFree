#ifndef GRID_H
#define GRID_H

#include "paint_common.h"
#include "Point.h"

#include <cassert>
#include <vector>
#include <QDebug>
#include <QRect>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>

class GridMouseEventHandler : public QGraphicsRectItem {
public:
    GridMouseEventHandler(const QRect& rect) : QGraphicsRectItem(rect) {
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

class Grid : public QObject, private LocatorRegister<Grid> {
    Q_OBJECT
public:
    Grid(int _pixelSize, int _size, QObject* parent = 0);
    ~Grid();

    Point locate(QPointF point);
    QRect getGridRect(Point point);
    bool isInside(QPointF point);
    qreal getGridSize();
private:

    std::vector<int> line;

    int pixelSize, size;
    qreal gridSize;
    ItemList* itemList;

    void init();
    void paintLine(int x1, int y1, int x2, int y2);
    void paint();
    bool isInside(qreal x);
    int locate(qreal x);
};

#endif // GRID_H
