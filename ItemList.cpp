#include "ItemList.h"

ItemList::ItemList(QObject *parent) : QObject(parent) {}

ItemList::~ItemList() {
    clear();
}

void ItemList::clear() {
    for(QGraphicsItem* i : list) {
        Scene::removeItem(i);
        delete i;
    }
    list.clear();
}

void ItemList::addItem(QGraphicsItem *item) {
    Scene::addItem(item);
    list.push_back(item);
}
