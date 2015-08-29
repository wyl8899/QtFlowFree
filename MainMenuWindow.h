#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include "paint_common.h"
#include "FlowFreeWindowBase.h"

#include <QObject>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class MainMenuWindow : public QObject, public FlowFreeWindowBase {
    Q_OBJECT
public:
    explicit MainMenuWindow(QObject* parent = 0) : QObject(parent) {
        itemList = new ItemList(this);
        auto button = new QPushButton();
        button->setText("Retry");
        auto proxy = new QGraphicsProxyWidget();
        proxy->setWidget(button);
        itemList->addItem(proxy);
    }

    Mode mode() {
        return common::MainMenuWindow;
    }

private:
    ItemList* itemList;
};

#endif // MAINMENUWINDOW_H
