#include "GameWindow.h"
#include "MainMenuWindow.h"
#include "WindowSelector.h"

GameWindow::GameWindow(GameConfig config, QObject *parent) : QObject(parent) {
    auto gridSize = common::PredefinedSize::SceneWidth * 0.95;
    grid = new Grid(gridSize, config.size, this);
    puzzle = new Puzzle(config, this);
    mouseDragCircle = new MouseDragCircle(this);

    itemList = new ItemList(this);

    auto backText = new ClickableText();
    backText->setHtml(R"(<p style="font-family:Arial;font-size:27px;color:white">Back</p>)");
    backText->setZValue(common::VisibleItemID::Text);
    backText->setX(common::PredefinedSize::SceneWidth * 0.025);
    backText->setY(20);
    connect(backText, &ClickableText::released, [](){WindowSelector::select(new MainMenuWindow);});
    itemList->addItem(backText);
}

GameWindow::~GameWindow(){
    delete mouseDragCircle;
    delete puzzle;
    delete grid;
}
