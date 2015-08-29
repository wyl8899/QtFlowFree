#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include "paint_common.h"
#include "FlowFreeWindowBase.h"
#include "GameConfig.h"
#include "GameWindow.h"
#include "WindowSelector.h"

#include <QObject>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QTextDocument>
#include <QTextOption>

class ClickableText : public QGraphicsTextItem {
    Q_OBJECT
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) {
        Q_UNUSED(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        if (this->contains(event->pos()))
            emit released();
    }
signals:
    void released();
};

class MainMenuWindow : public QObject, public FlowFreeWindowBase {
    Q_OBJECT
public:
    explicit MainMenuWindow(QObject* parent = 0);

    Mode mode() {
        return common::MainMenuWindow;
    }

private:
    ItemList* itemList;

public slots:
    void play();
};

#endif // MAINMENUWINDOW_H
