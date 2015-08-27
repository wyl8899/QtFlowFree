#ifndef POINT_H
#define POINT_H

#include <QDebug>
#include <QString>
#include <algorithm>

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point &rhs) {
        return x == rhs.x && y == rhs.y;
    }

    bool isAdjacentTo(const Point &p) {
        return std::abs(x - p.x) + std::abs(y - p.y) == 1;
    }

    QString inspect() {
        return QString("(%1, %2)").arg(x).arg(y);
    }
};

QDebug operator<<(QDebug debug, const Point& point);

#endif // POINT_H
