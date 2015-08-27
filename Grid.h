#ifndef GRID_H
#define GRID_H

#include "Point.h"
#include "Itemlist.h"

#include <cassert>
#include <vector>

class Grid: public QObject {
    Q_OBJECT
public:
    Grid(int _pixelSize, int _size, QObject* parent) : QObject(parent) {
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

    static void locate(int x, int y) {
        instance()->_locate(x, y);
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
        QGraphicsItem* line;
        line = new QGraphicsLineItem(0, 0, pixelSize, pixelSize);
        itemList->addItem(line);
    }

    Point _locate(int x, int y) {
        return Point(locate(x), locate(y));
    }

    int locate(int x) {
        assert(x >= 0);
        assert(x <= pixelSize);
        for (int i = 0; i < size; ++i) {
            if (x < line[i + 1])
                return i;
        }
    }

};

#endif // GRID_H
