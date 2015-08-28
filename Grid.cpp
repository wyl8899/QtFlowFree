#include "Grid.h"

Grid* Grid::singleton = nullptr;

Grid::Grid(int _pixelSize, int _size, QObject *parent) : QObject(parent) {
    singleton = this;
    pixelSize = _pixelSize;
    size = _size;
    init();
    paint();
}

Grid::~Grid() {
    singleton = nullptr;
}

void Grid::init() {
    gridSize = (double)pixelSize / size;
    for (int i = 0; i <= size; ++i) {
        line.push_back((int)round(gridSize * i));
    }
}

void Grid::paintLine(int x1, int y1, int x2, int y2) {
    auto line = new QGraphicsLineItem(x1, y1, x2, y2);
    auto itemID = common::VisibleItemID::GridLine;
    line->setZValue(itemID);
    QColor color = common::getColor(itemID);
    line->setPen(QPen(color));
    itemList->addItem(line);
}

qreal Grid::_getGridSize() {
    return gridSize;
}

void Grid::paint() {
    itemList = new ItemList(this);
    for (int i = 0; i <= size; ++i) {
        int pos = line[i];
        paintLine(0, pos, pixelSize, pos);
        paintLine(pos, 0, pos, pixelSize);
    }
}

bool Grid::_isInside(QPoint point) {
    return isInside(point.x()) && isInside(point.y());
}

Point Grid::_locate(QPoint point) {
    return Point(locate(point.x()), locate(point.y()));
}

QRect Grid::_getGridRect(Point point) {
    int x = point.x, y = point.y;
    return QRect(QPoint(line[x], line[y]), QPoint(line[x+1], line[y+1]));
}

bool Grid::isInside(int x) {
    return x >= 0 && x <= pixelSize;
}

int Grid::locate(int x) {
    assert(isInside(x));
    for (int i = 0; i < size; ++i) {
        if (x <= line[i + 1])
            return i;
    }
    assert(false);
    return 0;
}
