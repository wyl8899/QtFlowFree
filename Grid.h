#ifndef GRID_H
#define GRID_H

#include "paint_common.h"
#include "Point.h"

#include <cassert>
#include <vector>
#include <QDebug>
#include <QRect>
#include <QPoint>

class Grid: public QObject, private LocatorRegister<Grid> {
    Q_OBJECT
public:
    Grid(int _pixelSize, int _size, QObject* parent = 0);
    ~Grid();

    Point locate(QPoint point);
    QRect getGridRect(Point point);
    bool isInside(QPoint point);
    qreal getGridSize();
private:

    std::vector<int> line;

    int pixelSize, size;
    qreal gridSize;
    ItemList* itemList;

    void init();
    void paintLine(int x1, int y1, int x2, int y2);
    void paint();
    bool isInside(int x);
    int locate(int x);
};

#endif // GRID_H
