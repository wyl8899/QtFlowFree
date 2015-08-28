#ifndef BOARD_H
#define BOARD_H

#include "paint_common.h"
#include "Point.h"
#include "GameConfig.h"
#include "Grid.h"

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMargins>
#include <algorithm>
#include <vector>
#include <cassert>

struct PointPair {
    Point first, second;

    typedef std::pair<Point, Point> Pair;

    PointPair() {}
    PointPair(Point x, Point y) : first(x), second(y) {}
    PointPair(const Pair& pair) : first(pair.first), second(pair.second) {}

    inline bool contains(Point point) {
        return first == point || second == point;
    }
    inline Point getTheOther(Point point) {
        if (first == point)
        return second;
        if (second == point)
        return first;
        assert(false);
    }

    inline QString inspect() {
        return QString("[") + first.inspect() + ", " + second.inspect() + "]";
    }
};

class Board : public QObject {
    Q_OBJECT
public:
    Board(GameConfig config, QObject* parent);

    ~Board();

    static Board* instance() {
        assert(singleton != nullptr);
        return singleton;
    }

    static int getIndex(Point point) {
        return instance()->_getIndex(point);
    }
    static bool isStart(Point point) {
        return instance()->_isStart(point);
    }
    static Point getTheOther(int index, Point point) {
        return instance()->_getTheOther(index, point);
    }

private:
    enum {
        PointNotFound = -1,
    };

    static Board* singleton;
    ItemList* itemList;
    std::vector<PointPair> points;

    void paint();
    void paintPoint(Point point, int index);

    int _getIndex(Point point);
    bool _isStart(Point point);
    Point _getTheOther(int index, Point point);
};

#endif // BOARD_H
