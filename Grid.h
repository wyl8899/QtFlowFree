#ifndef GRID_H
#define GRID_H

#include "Point.h"
#include "Itemlist.h"

#include <cassert>
#include <vector>

class Grid: public QObject {
    Q_OBJECT
public:
    Grid(int _pixelSize, int _size) {
        pixelSize = _pixelSize;
        size = _size;
        init();
        paint();
    }

    void init() {
        double gridSize = (double)pixelSize / size;
        for (int i = 0; i <= size; ++i) {
            line.push_back((int)round(gridSize * i));
        }
    }

    void paint() {
        itemList = new ItemList(this);
    }

    Point locate(int x, int y) {
        return Point(locate(x), locate(y));
    }

private:
    std::vector<int> line;

    int pixelSize, size;
    ItemList* itemList;

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
