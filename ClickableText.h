#ifndef CLICKABLETEXT_H
#define CLICKABLETEXT_H

#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class ClickableText : public QGraphicsTextItem {
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
signals:
    void released();
};

#endif // CLICKABLETEXT_H
