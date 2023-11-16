#include "screenshot-area-selection.hpp"

AreaSelect::AreaSelect()
{
    display = XOpenDisplay(NULL);
    root = XDefaultRootWindow(display);
}

AreaSelect::~AreaSelect()
{
    XCloseDisplay(display);
}

int* AreaSelect::getMousePos(int* mousePos)
{
    Window rootReturn;
    unsigned int mask;

    XQueryPointer(display, root, &rootReturn, &rootReturn, &mousePos[0], &mousePos[1], &mousePos[0], &mousePos[1], &mask);

    return mousePos;
}

int* AreaSelect::getAreaSelection(int* area)
{
    // get mouse event handler

    // on mouse event mouse1 down take initial pos
    // on mouse event mouse1 up take after pos

    // calculate rect dimensions
    // return rect dimensions

}
