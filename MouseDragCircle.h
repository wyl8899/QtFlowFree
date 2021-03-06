#ifndef MOUSEDRAGCIRCLE_H
#define MOUSEDRAGCIRCLE_H

#include "paint_common.h"
#include <QObject>
#include <QDebug>

class MouseDragCircle : public QObject, private LocatorRegister<MouseDragCircle> {
    Q_OBJECT
public:
    explicit MouseDragCircle(QObject* parent = 0);

    ~MouseDragCircle();

    void setColor(QColor color);
    void show(QPointF point);
    void move(QPointF point);
    void show();
    void hide();
private:
    enum Status {
        Show,
        Hide
    };

    ItemList* itemList;
    QColor color;
    Status status;

    void paint(QPointF point);
};

#endif // MOUSEDRAGCIRCLE_H

