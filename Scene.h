#ifndef SCENE_H
#define SCENE_H

#include "Locator.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <cassert>

class Scene : public QObject, private LocatorRegister<Scene> {
    Q_OBJECT
public:
    explicit Scene(QObject* parent = 0);
    ~Scene();

    QGraphicsScene* getScene();
    void addItem(QGraphicsItem* item);
    void removeItem(QGraphicsItem* item);
private:
    QGraphicsScene* scene;
};

#endif // SCENE_H
