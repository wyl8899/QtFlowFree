#include "Background.h"
#include "View.h"

Background::Background(QObject *parent) : QObject(parent) {
    paint();
}

void Background::paint() {
    auto itemList = new ItemList(this);
    auto viewRect = Locator<View>()->rect();
    auto rect = new QGraphicsRectItem(viewRect);
    auto itemID = common::VisibleItemID::Background;
    rect->setZValue(itemID);
    QColor color = common::getColor(itemID);
    rect->setPen(Qt::NoPen);
    rect->setBrush(QBrush(color));
    itemList->addItem(rect);
}
