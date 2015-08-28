#include "Pipe.h"
#include "Strategy.h"

Pipe::Pipe(Strategy *_strategy, int _index, Point st, Point ed) {
    strategy = _strategy;
    index = _index;
    path.push_back(st);
    dest = ed;
    itemList = new ItemList(this);
    state = Drawing;
    paint();
}

QPoint Pipe::getCenter(Point point) {
    return Grid::getGridRect(point).center();
}

void Pipe::paintLine(QPoint st, QPoint ed) {
    auto line = new QGraphicsLineItem(st.x(), st.y(), ed.x(), ed.y());
    const auto itemID = common::VisibleItemID::PipeLine;
    line->setZValue(itemID);
    QColor color = common::getColor(itemID, index);
    QBrush brush(color);
    QPen pen(brush, Grid::getGridSize() * 0.3, Qt::SolidLine, Qt::RoundCap);
    line->setPen(pen);
    itemList->addItem(line);
}

void Pipe::paintLines() {
    std::vector<QPoint> centers;
    for (auto& point : path) {
        if (isTemporarilyOccupied(point))
            break;
        centers.push_back(getCenter(point));
    }
    for (size_t i = 1; i < centers.size(); ++i) {
        QPoint& st = centers[i - 1];
        QPoint& ed = centers[i];
        paintLine(st, ed);
    }
}

void Pipe::paintBackground(QRect rect){
    auto rectItem = new QGraphicsRectItem(rect);
    auto itemID = common::VisibleItemID::GridBgColor;
    QColor color = common::getColor(itemID, index);
    rectItem->setPen(Qt::NoPen);
    rectItem->setBrush(QBrush(color));
    rectItem->setZValue(itemID);
    itemList->addItem(rectItem);
}



void Pipe::paintBackgrounds() {
    for (auto& point : path) {
        QRect rect = Grid::getGridRect(point);
        paintBackground(rect);
    }
}

void Pipe::paint() {
    itemList->clear();
    paintLines();
    if (state == NotDrawing) {
        paintBackgrounds();
    }
}

QString Pipe::inspect() {
    QStringList list;
    for (auto& p : path) {
        list << p.inspect();
    }
    return QString("Pipe: %1[%2]").arg(isConnected()?"+":"").arg(list.join(", "));
}

bool Pipe::contains(Point point) {
    return getIndex(point) != PointNotFound;
}

bool Pipe::isConnected() {
    return *path.rbegin() == dest;
}

bool Pipe::isTemporarilyOccupied(Point point) {
    if (state == Drawing)
        return false;
    else
        return strategy->isTemporarilyOccupied(point);
}

void Pipe::start(Point point) {
    assert(state == NotDrawing);
    state = Drawing;
    extend(point);
}

void Pipe::extend(Point point) {
    assert(state == Drawing);
    if (contains(point)) {
        int index = getIndex(point);
        path.resize(index + 1);
    } else {
        if (isConnected())
            return;
        Point currentEnd = *path.rbegin();
        if (currentEnd.isAdjacentTo(point)) {
            path.push_back(point);
        }
    }
    paint();
}

void Pipe::intercept(Point point) {
    assert(state == NotDrawing);
    if (contains(point)) {
        int index = getIndex(point);
        path.resize(index);
    }
    paint();
}

void Pipe::finish() {
    assert(state == Drawing);
    state = NotDrawing;
}

int Pipe::getIndex(Point point) {
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == point)
            return i;
    }
    return PointNotFound;
}
