#ifndef GRID_H
#define GRID_H

#include "paint_common.h"
#include "Point.h"

#include <cassert>
#include <vector>
#include <QDebug>
#include <QRect>
#include <QPoint>

class Grid: public QObject {
    Q_OBJECT
public:
    Grid(int _pixelSize, int _size, QObject* parent = 0);

    ~Grid();

    static Grid* instance() {
        assert(singleton != nullptr);
        return singleton;
    }

    static QRect getGridRect(Point point) {
        return instance()->_getGridRect(point);
    }

    static qreal getGridSize() {
        return instance()->_getGridSize();
    }

    static Point locate(QPoint point) {
        return instance()->_locate(point);
    }

    static bool isInside(QPoint point) {
        return instance()->_isInside(point);
    }

private:
    static Grid* singleton;

    std::vector<int> line;

    int pixelSize, size;
    qreal gridSize;
    ItemList* itemList;

    void init();
    void paintLine(int x1, int y1, int x2, int y2);
    qreal _getGridSize();
    void paint();
    bool _isInside(QPoint point);
    Point _locate(QPoint point);
    QRect _getGridRect(Point point);
    bool isInside(int x);
    int locate(int x);
};

#endif // GRID_H
