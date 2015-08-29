#ifndef FLOWFREEWINDOWBASE_H
#define FLOWFREEWINDOWBASE_H

#include "common.h"
#include "View.h"

#include <QMouseEvent>

class FlowFreeWindowBase {
protected:
    typedef common::WindowMode Mode;
public:
    virtual ~FlowFreeWindowBase() {}
    virtual Mode mode() = 0;
};

#endif // FLOWFREEWINDOWBASE_H
