#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <cassert>

class Scene : QObject {
    Q_OBJECT
public:
    explicit Scene(QObject* parent = 0) : QObject(parent) {
        _instance = this;
    }

    ~Scene() {
        _instance = nullptr;
    }

    static Scene* instance() {
        assert(_instance != nullptr);
        return _instance;
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
    static Scene* _instance;
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
