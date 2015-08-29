#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "paint_common.h"

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsLineItem>

#include <cstdlib>

class FloatingLine : public QGraphicsObject {
    Q_OBJECT
public:
    explicit FloatingLine(QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
public:
    QGraphicsLineItem* lineItem;
};

class Background : public QObject {
    Q_OBJECT
public:
    Background(QObject* parent = 0);

    void paint();
private:
    ItemList* itemList;
    QGraphicsRectItem* bgRect;
public slots:
    void addFloatingLine();
};

#endif // BACKGROUND_H
