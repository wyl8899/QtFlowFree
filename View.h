#ifndef VIEW_H
#define VIEW_H

#include "common.h"
#include "Grid.h"
#include "Puzzle.h"
#include "MouseDragCircle.h"

#include <QGraphicsView>
#include <QMouseEvent>

class QGraphicsScene;

class View : public QGraphicsView, private LocatorRegister<View> {
    Q_OBJECT
public:
    explicit View(QWidget* parent = 0);
protected:
    void wheelEvent(QWheelEvent* event);
};

#endif // VIEW_H

