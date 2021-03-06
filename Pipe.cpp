#include "Pipe.h"
#include "Strategy.h"
#include "MouseDragCircle.h"

#include <QSound>

Pipe::Pipe(Strategy *_strategy, int _index, Point st, Point ed) {
    strategy = _strategy;
    index = _index;
    path.push_back(st);
    dest = ed;
    itemList = new ItemList(this);
    state = NotDrawing;
    start(st);
    paint();
}

QPointF Pipe::getCenter(Point point) {
    return Locator<Grid>()->getGridRect(point).center();
}

void Pipe::paintLine(QPointF st, QPointF ed) {
    auto line = new QGraphicsLineItem(st.x(), st.y(), ed.x(), ed.y());
    const auto itemID = common::VisibleItemID::PipeLine;
    QColor color = common::getColor(itemID, index);
    QBrush brush(color);
    qreal width = Locator<Grid>()->getGridSize() * common::predefinedSize::PipeWidthOverGridSize;
    QPen pen(brush, width, Qt::SolidLine, Qt::RoundCap);
    line->setPen(pen);
    line->setZValue(itemID);
    itemList->addItem(line);
}

void Pipe::paintLines() {
    std::vector<QPointF> centers;
    for (auto& point : path) {
        if (isTemporarilyOccupied(point))
            break;
        centers.push_back(getCenter(point));
    }
    for (size_t i = 1; i < centers.size(); ++i) {
        QPointF& st = centers[i - 1];
        QPointF& ed = centers[i];
        paintLine(st, ed);
    }
}

void Pipe::paintBackground(QRectF rect){
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
        QRectF rect = Locator<Grid>()->getGridRect(point);
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
    QColor color = common::getColor(common::VisibleItemID::MouseDragCircle, index);
    Locator<MouseDragCircle>()->setColor(color);
    Locator<MouseDragCircle>()->show();
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
        if (isConnected()) {
            QSound::play(":/Sounds/Sounds/Broken.wav");
        }
        int index = getIndex(point);
        path.resize(index);
    }
    paint();
}

void Pipe::finish() {
    assert(state == Drawing);
    state = NotDrawing;
    if (isConnected()) {
        QSound::play(":/Sounds/Sounds/Flow.wav");
    }
}

int Pipe::getIndex(Point point) {
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == point)
            return i;
    }
    return PointNotFound;
}
