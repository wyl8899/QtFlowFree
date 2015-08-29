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
