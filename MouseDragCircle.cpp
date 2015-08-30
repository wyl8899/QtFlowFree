#include "MouseDragCircle.h"

MouseDragCircle::MouseDragCircle(QObject *parent) : QObject(parent) {
    itemList = new ItemList(this);
    status = Status::Hide;
}

MouseDragCircle::~MouseDragCircle() {
}

void MouseDragCircle::setColor(QColor color) {
    this->color = color;
}

void MouseDragCircle::show(QPointF point) {
    status = Status::Show;
    paint(point);
}

void MouseDragCircle::show() {
    status = Status::Show;
}

void MouseDragCircle::move(QPointF point) {
    if (status == Status::Show)
        paint(point);
}

void MouseDragCircle::hide() {
    status = Status::Hide;
    itemList->clear();
}

void MouseDragCircle::paint(QPointF point) {
    itemList->clear();
    qreal diameter = common::predefinedSize::MouseDragCircleSize;
    qreal radius = diameter * 0.5;
    qreal x = point.x() - radius, y = point.y() - radius;
    auto circle = new QGraphicsEllipseItem(x, y, diameter, diameter);
    auto itemID = common::VisibleItemID::MouseDragCircle;
    circle->setPen(Qt::NoPen);
    circle->setBrush(QBrush(this->color));
    circle->setZValue(itemID);
    itemList->addItem(circle);
}
