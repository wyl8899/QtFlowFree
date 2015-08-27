#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "Point.h"
#include "Itemlist.h"

#include <cassert>
#include <vector>
#include <QDebug>
#include <QRect>
#include <QPoint>

class Grid: public QObject {
    Q_OBJECT
public:
    Grid(int _pixelSize, int _size, QObject* parent = 0) : QObject(parent) {
        singleton = this;
        pixelSize = _pixelSize;
        size = _size;
        init();
        paint();
    }

    ~Grid() {
        singleton = nullptr;
    }

    static Grid* instance() {
        assert(singleton != nullptr);
        return singleton;
    }

    static QRect getGridRect(Point point) {
        return instance()->_getGridRect(point);
    }

    static Point locate(QPoint point) {
        return instance()->_locate(point);
    }
private:
    static Grid* singleton;

    std::vector<int> line;

    int pixelSize, size;
    ItemList* itemList;

    void init() {
        double gridSize = (double)pixelSize / size;
        for (int i = 0; i <= size; ++i) {
            line.push_back((int)round(gridSize * i));
        }
    }

    void paint() {
        itemList = new ItemList(this);
        for (int i = 0; i <= size; ++i) {
            int pos = line[i];
            QGraphicsItem* verticalLine = new QGraphicsLineItem(0, pos, pixelSize, pos);
            QGraphicsItem* horizontalLine = new QGraphicsLineItem(pos, 0, pos, pixelSize);
            verticalLine->setZValue(zValues::GridLine);
            horizontalLine->setZValue(zValues::GridLine);
            itemList->addItem(verticalLine);
            itemList->addItem(horizontalLine);
        }
    }

    Point _locate(QPoint point) {
        return Point(locate(point.x()), locate(point.y()));
    }

    QRect _getGridRect(Point point) {
        int x = point.x, y = point.y;
        return QRect(QPoint(line[x], line[y]), QPoint(line[x+1], line[y+1]));
    }

    int locate(int x) {
        assert(x >= 0);
        assert(x <= pixelSize);
        for (int i = 0; i < size; ++i) {
            if (x <= line[i + 1])
                return i;
        }
        assert(false);
        return 0;
    }

};

#endif // GRID_H
