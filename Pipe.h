#ifndef PIPE_H
#define PIPE_H

#include "common.h"
#include "Itemlist.h"
#include "Point.h"
#include "Grid.h"

#include <QObject>
#include <QString>
#include <QPoint>
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
        state = Drawing;
        paint();
    }

    QPoint getCenter(Point point) {
        return Grid::getGridRect(point).center();
    }

    void paintLine(QPoint st, QPoint ed) {
        auto line = new QGraphicsLineItem(st.x(), st.y(), ed.x(), ed.y());
        line->setZValue(zValues::PipeLine);
        itemList->addItem(line);
    }

    void paintLines();

    void paintBackgrounds() {
        // TODO
    }

    void paint() {
        itemList->clear();
        paintLines();
        if (state == NotDrawing) {
            paintBackgrounds();
        }
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

    bool isTemporarilyOccupied(Point point);

    void start(Point point) {
        assert(state == NotDrawing);
        state = Drawing;
        extend(point);
    }

    void extend(Point point) {
        assert(state == Drawing);
        if (contains(point)) {
            int index = getIndex(point);
            path.resize(index + 1);
        } else {
            Point currentEnd = *path.rbegin();
            if (currentEnd.isAdjacentTo(point)) {
                path.push_back(point);
            }
        }
        paint();
    }

    void intercept(Point point) {
        assert(state == NotDrawing);
        if (contains(point)) {
            int index = getIndex(point);
            path.resize(index);
        }
        paint();
    }

    void finish() {
        assert(state == Drawing);
        state = NotDrawing;
    }

private:
    enum {
        PointNotFound = -1
    };

    enum State {
        NotDrawing,
        Drawing
    };

    Point dest;
    std::vector<Point> path;
    State state;

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

