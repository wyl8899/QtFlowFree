#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Scene.h"
#include <vector>

class ItemList : QObject {
    Q_OBJECT
public:
    explicit ItemList(QObject* parent = 0) : QObject(parent) {}

    ~ItemList() {
        clear();
    }

    void clear() {
        for(auto &i : list) {
            Scene::removeItem(i);
        }
    }

    void addItem(QGraphicsItem* item) {
        Scene::addItem(item);
        list.push_back(item);
    }

private:
    std::vector<QGraphicsItem*> list;
};

#endif // ITEMLIST_H
