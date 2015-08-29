#include "View.h"
#include "WindowSelector.h"

View::View(QWidget *parent) : QGraphicsView(parent) {
}

void View::wheelEvent(QWheelEvent *event) {
    Q_UNUSED(event);
    // Do Nothing
}
