#ifndef WINDOWSELECTOR_H
#define WINDOWSELECTOR_H

#include "common.h"
#include "FlowFreeWindowBase.h"

class WindowSelector {
private:
    typedef FlowFreeWindowBase Window;
    typedef common::WindowMode Mode;

public:
    static void show(Window* window) {
        kill();
        currentWindow = window;
        currentMode = window->mode();
    }

    static void kill() {
        if (currentWindow != nullptr)
            delete currentWindow;
        currentWindow = nullptr;
    }

private:
    static Window* currentWindow;
    static Mode currentMode;
};

#endif // WINDOWSELECTOR_H
