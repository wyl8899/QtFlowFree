#include "MainMenuWindow.h"
#include "ClickableText.h"

MainMenuWindow::MainMenuWindow(QObject *parent) : QObject(parent) {
    itemList = new ItemList(this);

    auto flowText = new QGraphicsTextItem();
    flowText->setHtml(R"(<p style="font-size:90px;font-family:Arial"><span style="color:red">f</span><span style="color:green">l</span><span style="color:blue">o</span><span style="color:yellow">w</span></p>)");
    Scene::setAlignHCenter(flowText);
    flowText->setY(common::predefinedSize::SceneHeight * 0.13);
    flowText->setZValue(common::VisibleItemID::Text);
    itemList->addItem(flowText);

    auto playText = new ClickableText();
    playText->setHtml(R"(<p style="font-size:50px;font-family:Arial;color:white">free play</p>)");
    Scene::setAlignHCenter(playText);
    playText->setY(common::predefinedSize::SceneHeight * 0.33);
    connect(playText, &ClickableText::released, [](){
        WindowSelector::show(new GameWindow(0));
    });
    playText->setZValue(common::VisibleItemID::Text);
    itemList->addItem(playText);
}
