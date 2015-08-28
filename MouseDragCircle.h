#ifndef MOUSEDRAGCIRCLE_H
#define MOUSEDRAGCIRCLE_H

#include "paint_common.h"
#include <QObject>
#include <QDebug>

class MouseDragCircle : public QObject {
    Q_OBJECT
public:
    explicit MouseDragCircle(QObject* parent = 0) : QObject(parent) {
        itemList = new ItemList(this);
        status = Status::Hide;
    }

    ~MouseDragCircle() {
    }

    static MouseDragCircle* instance() {
        if (singleton == nullptr)
            singleton = new MouseDragCircle();
        return singleton;
    }
    static void setColor(QColor color) {
        instance()->_setColor(color);
    }
    static void show(QPoint point) {
        instance()->_show(point);
    }
    static void show() {
        instance()->_show();
    }
    static void move(QPoint point) {
        instance()->_move(point);
    }
    static void hide() {
        instance()->_hide();
    }

private:
    static MouseDragCircle* singleton;
    ItemList* itemList;
    QColor color;

    enum Status {
        Show,
        Hide
    };

    Status status;

    void paint(QPoint point) {
        itemList->clear();
        qreal diameter = common::PredefinedSize::MouseDragCircleSize;
        qreal radius = diameter * 0.5;
        qreal x = point.x() - radius, y = point.y() - radius;
        auto circle = new QGraphicsEllipseItem(x, y, diameter, diameter);
        auto itemID = common::VisibleItemID::MouseDragCircle;
        circle->setPen(Qt::NoPen);
        circle->setBrush(QBrush(this->color));
        circle->setZValue(itemID);
        itemList->addItem(circle);
    }

    void _setColor(QColor color) {
        this->color = color;
    }
    void _show(QPoint point) {
        status = Status::Show;
        paint(point);
    }
    void _show() {
        status = Status::Show;
    }
    void _move(QPoint point) {
        if (status == Status::Show)
            paint(point);
    }
    void _hide() {
        status = Status::Hide;
        itemList->clear();
    }
};

#endif // MOUSEDRAGCIRCLE_H

