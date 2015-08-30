#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T14:13:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT		 += multimedia

TARGET = FlowFree
TEMPLATE = app
CONFIG += c++11

SOURCES +=\
        MainWindow.cpp \
    Main.cpp \
    Scene.cpp \
    Board.cpp \
    Point.cpp \
    test.cpp \
    Grid.cpp \
    Puzzle.cpp \
    Pipe.cpp \
    Background.cpp \
    predefinedColor.cpp \
    Strategy.cpp \
    GameConfig.cpp \
    ItemList.cpp \
    MouseDragCircle.cpp \
    Locator.cpp \
    View.cpp \
    WindowSelector.cpp \
    MainMenuWindow.cpp \
    GameWindow.cpp \
    ClickableText.cpp \
    builtinLevels.cpp

HEADERS  += MainWindow.h \
    Grid.h \
    Point.h \
    Scene.h \
    Pipe.h \
    Strategy.h \
    Board.h \
    GameConfig.h \
    Puzzle.h \
    test.h \
    View.h \
    common.h \
    paint_common.h \
    predefinedColor.h \
    Background.h \
    ItemList.h \
    MouseDragCircle.h \
    Locator.h \
    FlowFreeWindowBase.h \
    GameWindow.h \
    MainMenuWindow.h \
    WindowSelector.h \
    ClickableText.h \
    builtinLevels.h

FORMS +=

RESOURCES += \
    resource.qrc
