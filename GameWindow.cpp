#include "GameWindow.h"
#include "MainMenuWindow.h"
#include "WindowSelector.h"
#include "builtinLevels.h"
#include "PuzzleSolver.h"

#include <QThread>
#include <QApplication>

GameWindow::GameWindow(int levelID, QObject *parent) : QObject(parent) {
    auto config = builtinLevels::getBuiltinLevel(levelID);

    auto gridSize = common::predefinedSize::SceneWidth * 0.95;
    grid = new Grid(gridSize, config.size, this);
    puzzle = new Puzzle(config, this);
    mouseDragCircle = new MouseDragCircle(this);

    itemList = new ItemList(this);

    const int textHMargin = 4;
    const int topTextY = 20;
    const int bottomTextY = common::predefinedSize::SceneHeight - 100;

    auto backText = new ClickableText();
    backText->setHtml(R"(<p style="font-family:Arial;font-size:27px;color:white">Back</p>)");
    backText->setZValue(common::VisibleItemID::Text);
    backText->setX(textHMargin);
    backText->setY(topTextY);
    connect(backText, &ClickableText::released, [](){WindowSelector::show(new MainMenuWindow);});
    itemList->addItem(backText);

    auto solveText = new ClickableText();
    solveText->setHtml(R"(<p style="font-family:Arial;font-size:27px;color:white">Auto Solve</p>)");
    solveText->setZValue(common::VisibleItemID::Text);
    solveText->setX(common::predefinedSize::SceneWidth - textHMargin - solveText->boundingRect().width());
    solveText->setY(topTextY);
    connect(solveText, &ClickableText::released, [this, levelID](){
        solve(levelID);
    });
    itemList->addItem(solveText);

    auto restartText = new ClickableText();
    restartText->setHtml(R"(<p style="font-family:Arial;font-size:27px;color:white">Restart</p>)");
    restartText->setZValue(common::VisibleItemID::Text);
    restartText->setY(bottomTextY);
    Scene::setAlignHCenter(restartText);
    connect(restartText, &ClickableText::released, [this, levelID](){
        this->newGame(levelID);
    });
    itemList->addItem(restartText);

    int prevLevelID = levelID - 1;
    if (prevLevelID >= 0) {
        auto prevText = new ClickableText();
        prevText->setHtml(R"(<p style="font-family:Arial;font-size:27px;color:white">Prev Level</p>)");
        prevText->setZValue(common::VisibleItemID::Text);
        prevText->setY(bottomTextY);
        prevText->setX(textHMargin);
        connect(prevText, &ClickableText::released, [this, prevLevelID](){
            this->newGame(prevLevelID);
        });
        itemList->addItem(prevText);
    }

    int nextLevelID = levelID + 1;
    if (nextLevelID < builtinLevels::NumOfBuiltinLevels) {
        auto nextText = new ClickableText();
        nextText->setHtml(R"(<p style="font-family:Arial;font-size:27px;color:white">Next Level</p>)");
        nextText->setZValue(common::VisibleItemID::Text);
        nextText->setY(bottomTextY);
        int textWidth = nextText->document()->idealWidth();
        nextText->setX(common::predefinedSize::SceneWidth - textWidth - textHMargin);
        connect(nextText, &ClickableText::released, [this, nextLevelID](){
            this->newGame(nextLevelID);
        });
        itemList->addItem(nextText);
    }
}

GameWindow::~GameWindow(){
    delete mouseDragCircle;
    delete puzzle;
    delete grid;
}

void GameWindow::solve(int levelID) {
    qDebug() << "GameWindow::solve" << levelID;
    auto config = builtinLevels::getBuiltinLevel(levelID);
    auto solver = new PuzzleSolver(config, this);
    solver->solve();
}

void GameWindow::newGame(int levelID) {
    WindowSelector::kill(); // Ensure singleton classes destruct first
    WindowSelector::show(new GameWindow(levelID));
}
