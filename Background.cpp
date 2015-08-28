#include "Background.h"

Background::Background(QObject *parent) : QObject(parent) {
    paint();
}

void Background::paint() {
    auto itemList = new ItemList(this);
    int size = common::PredefinedSize::SceneSize;
    auto rect = new QGraphicsRectItem(0, 0, size, size);
    auto itemID = common::VisibleItemID::Background;
    rect->setZValue(itemID);
    QColor color = common::getColor(itemID);
    rect->setPen(Qt::NoPen);
    rect->setBrush(QBrush(color));
    itemList->addItem(rect);
}
