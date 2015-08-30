#include "Board.h"
#include <QMarginsF>

Board::Board(GameConfig config, QObject *parent) : QObject(parent) {
    size = config.size;
    for (auto& i : config.points) {
        PointPair pair(i);
        points.push_back(pair);
    }
    paint();
}

Board::~Board() {
}

void Board::paint() {
    itemList = new ItemList(this);
    for (size_t i = 0; i < points.size(); ++i) {
        auto& pair = points[i];
        paintPoint(pair.first, i);
        paintPoint(pair.second, i);
    }
}

void Board::paintPoint(Point point, int index) {
    QRectF rect = Locator<Grid>()->getGridRect(point);
    qreal margin = Locator<Grid>()->getGridSize() * (1 - common::predefinedSize::CircleSizeOverGridSize);
    auto margins = QMarginsF(margin, margin, margin, margin);
    QRectF rectShrinked = rect.marginsRemoved(margins);
    auto circle = new QGraphicsEllipseItem(rectShrinked);
    auto itemID = common::VisibleItemID::Circle;
    QColor color = common::getColor(itemID, index);
    circle->setZValue(itemID);
    circle->setPen(Qt::NoPen);
    circle->setBrush(QBrush(color));
    itemList->addItem(circle);
}

int Board::getIndex(Point point) {
    for (size_t i = 0; i < points.size(); ++i) {
        PointPair& p = points[i];
        if (p.contains(point))
            return i;
    }
    return PointNotFound;
}

bool Board::isStart(Point point) {
    return getIndex(point) != PointNotFound;
}

Point Board::getTheOther(int index, Point point) {
    return points[index].getTheOther(point);
}

int Board::getSize() {
    return size;
}
