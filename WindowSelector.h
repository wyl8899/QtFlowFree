#ifndef WINDOWSELECTOR_H
#define WINDOWSELECTOR_H

#include "common.h"
#include "FlowFreeWindowBase.h"

class WindowSelector {
private:
    typedef FlowFreeWindowBase Window;
    typedef common::WindowMode Mode;

public:
    static void select(Window* window) {
        if (currentWindow != nullptr) {
            delete currentWindow;
        }
        currentWindow = window;
        currentMode = window->mode();
    }

private:
    static Window* currentWindow;
    static Mode currentMode;
};

#endif // WINDOWSELECTOR_H
