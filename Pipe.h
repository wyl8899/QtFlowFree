#ifndef PIPE_H
#define PIPE_H

#include "Itemlist.h"
#include "Point.h"

#include <QObject>
#include <QString>
#include <vector>

class Strategy;

class Pipe : public QObject {
    Q_OBJECT
public:
    Pipe(Strategy* _strategy, Point st, Point ed) {
        strategy = _strategy;
        path.push_back(st);
        dest = ed;
        itemList = new ItemList(this);
        paint();
    }

    void paint() {
        itemList->clear();
        // TODO
    }

    QString inspect() {
        QStringList list;
        for (auto& p : path) {
            list << p.inspect();
        }
        return QString("Pipe: %1[%2]").arg(isConnected()?"+":"").arg(list.join(", "));
    }

    std::vector<Point>& points() {
        return path;
    }

    bool contains(Point point) {
        return getIndex(point) != PointNotFound;
    }

    bool isConnected() {
        return *path.rbegin() == dest;
    }

    void extend(Point point) {
        if (contains(point)) {
            int index = getIndex(point);
            path.resize(index + 1);
        } else {
            Point currentEnd = *path.rbegin();
            if (currentEnd.isAdjacentTo(point)) {
                path.push_back(point);
            }
        }
    }

    void intercept(Point point) {
        if (contains(point)) {
            int index = getIndex(point);
            path.resize(index);
        }
    }

private:
    enum {
        PointNotFound = -1
    };

    Point dest;
    std::vector<Point> path;

    Strategy* strategy;

    ItemList* itemList;

    int getIndex(Point point) {
        for (size_t i = 0; i < path.size(); ++i) {
            if (path[i] == point)
                return i;
        }
        return PointNotFound;
    }
};

#endif // PIPE_H
