#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Scene.h"
#include <vector>

class ItemList : QObject {
    Q_OBJECT
public:
    explicit ItemList(QObject* parent = 0);
    ~ItemList();

    void clear();
    void addItem(QGraphicsItem* item);
private:
    std::vector<QGraphicsItem*> list;
};

#endif // ITEMLIST_H
