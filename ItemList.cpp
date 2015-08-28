#include "ItemList.h"

ItemList::ItemList(QObject *parent) : QObject(parent) {
    list.clear();
}

ItemList::~ItemList() {
    clear();
}

void ItemList::clear() {
    for(QGraphicsItem* i : list) {
        Locator<Scene>()->removeItem(i);
        delete i;
    }
    list.clear();
}

void ItemList::addItem(QGraphicsItem *item) {
    Locator<Scene>()->addItem(item);
    list.push_back(item);
}
