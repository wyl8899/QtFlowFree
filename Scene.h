#ifndef SCENE_H
#define SCENE_H

#include "Locator.h"
#include "common.h"

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

    static void setAlignHCenter(QGraphicsItem *item) {
        auto width = item->boundingRect().width();
        item->setX((common::predefinedSize::SceneWidth - width) * 0.5);
    }
    static void setAlignVCenter(QGraphicsItem *item) {
        auto height = item->boundingRect().height();
        item->setY((common::predefinedSize::SceneHeight - height) * 0.5);
    }

private:
    QGraphicsScene* scene;
};

#endif // SCENE_H
