#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <cassert>

class Scene : QObject {
    Q_OBJECT
public:
    explicit Scene(QObject* parent = 0) : QObject(parent) {
        singleton = this;
        scene = new QGraphicsScene(this);
    }

    ~Scene() {
        singleton = nullptr;
    }

    static Scene* instance() {
        assert(singleton != nullptr);
        return singleton;
    }

    static QGraphicsScene* getScene() {
        return instance()->_getScene();
    }

    static void addItem(QGraphicsItem* item) {
        instance()->_addItem(item);
    }
    static void removeItem(QGraphicsItem* item) {
        instance()->_removeItem(item);
    }

private:
    static Scene* singleton;
    QGraphicsScene* scene;

    QGraphicsScene* _getScene() {
        return scene;
    }
    void _addItem(QGraphicsItem* item) {
        scene->addItem(item);
    }
    void _removeItem(QGraphicsItem* item) {
        scene->removeItem(item);
    }
};

#endif // SCENE_H
