#include "MainMenuWindow.h"

MainMenuWindow::MainMenuWindow(QObject *parent) : QObject(parent) {
    itemList = new ItemList(this);

    auto flowText = new QGraphicsTextItem();
    flowText->setHtml(R"(<p style="font-size:90px;font-family:Arial"><span style="color:red">f</span><span style="color:green">l</span><span style="color:blue">o</span><span style="color:yellow">w</span></p>)");
    Scene::setAlignHCenter(flowText);
    flowText->setY(common::PredefinedSize::SceneHeight * 0.13);
    flowText->setZValue(common::VisibleItemID::Text);
    itemList->addItem(flowText);

    auto playText = new ClickableText();
    playText->setHtml(R"(<p style="font-size:50px;font-family:Arial;color:white">free play</p>)");
    Scene::setAlignHCenter(playText);
    playText->setY(common::PredefinedSize::SceneHeight * 0.33);
    connect(playText, SIGNAL(released()), this, SLOT(play()));
    playText->setZValue(common::VisibleItemID::Text);
    itemList->addItem(playText);
}

void MainMenuWindow::play() {
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
