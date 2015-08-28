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

    QString inspect() {
        return QString("[") + first.inspect() + ", " + second.inspect() + "]";
    }
};

QDebug operator<<(QDebug debug, const PointPair& pair);

class Board : public QObject {
    Q_OBJECT
public:
    Board(GameConfig config, QObject* parent) : QObject(parent) {
        singleton = this;
        for (auto& i : config.points) {
            PointPair pair(i);
            points.push_back(pair);
        }
        paint();
    }

    ~Board() {
        singleton = nullptr;
    }

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

    void paint() {
        itemList = new ItemList(this);
        for (size_t i = 0; i < points.size(); ++i) {
            auto& pair = points[i];
            paintPoint(pair.first, i);
            paintPoint(pair.second, i);
        }
    }

    void paintPoint(Point point, int index) {
        QRect rect = Grid::getGridRect(point);
        qreal margin = Grid::getGridSize() * 0.1;
        QMargins margins = QMargins(margin, margin, margin, margin);
        QRect rectShrinked = rect.marginsRemoved(margins);
        auto circle = new QGraphicsEllipseItem(rectShrinked);
        auto itemID = common::VisibleItemID::Circle;
        QColor color = common::getColor(itemID, index);
        circle->setZValue(itemID);
        circle->setPen(Qt::NoPen);
        circle->setBrush(QBrush(color));
        itemList->addItem(circle);
    }

    int _getIndex(Point point) {
        for (size_t i = 0; i < points.size(); ++i) {
            PointPair& p = points[i];
            if (p.contains(point))
                return i;
        }
        return PointNotFound;
    }

    bool _isStart(Point point) {
        return getIndex(point) != PointNotFound;
    }

    Point _getTheOther(int index, Point point) {
        return points[index].getTheOther(point);
    }
};

#endif // BOARD_H
