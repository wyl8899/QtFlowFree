#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T14:13:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    Grid.cpp

HEADERS  += MainWindow.h \
    Grid.h \
    Point.h \
    Itemlist.h \
    Scene.h \
    Pipe.h \
    Strategy.h \
    Board.h \
    GameConfig.h \
    Puzzle.h \
    test.h
