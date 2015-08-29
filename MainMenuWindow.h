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
    explicit MainMenuWindow(QObject* parent = 0) : QObject(parent) {
        itemList = new ItemList(this);

        playText = new ClickableText();
        playText->setPlainText("Play");
        playText->setDefaultTextColor("white");
        connect(playText, SIGNAL(released()), this, SLOT(play()));

        itemList->addItem(playText);
    }

    Mode mode() {
        return common::MainMenuWindow;
    }

private:
    ItemList* itemList;
    ClickableText* playText;

public slots:
    void play() {
        GameConfig config;
        config.size = 5;
        config.add(4, 0, 4, 2);
        config.add(3, 3, 4, 4);
        config.add(0, 4, 3, 4);
        config.add(1, 1, 0, 3);
        config.add(1, 2, 3, 2);

        auto gameWindow = new GameWindow(config);

        // Warning: will delete this MainMenuWindow instance
        WindowSelector::select(gameWindow);
    }
};

#endif // MAINMENUWINDOW_H
