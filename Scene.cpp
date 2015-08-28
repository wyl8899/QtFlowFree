#include "Scene.h"

Scene::Scene(QObject *parent) : QObject(parent) {
    scene = new QGraphicsScene(this);
}

Scene::~Scene() {
}

QGraphicsScene *Scene::getScene() {
    return scene;
}

void Scene::addItem(QGraphicsItem *item) {
    scene->addItem(item);
}

void Scene::removeItem(QGraphicsItem *item) {
    scene->removeItem(item);
}
