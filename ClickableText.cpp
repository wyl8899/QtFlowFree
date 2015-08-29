#include "ClickableText.h"

void ClickableText::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
}

void ClickableText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (this->contains(event->pos()))
        emit released();
}
