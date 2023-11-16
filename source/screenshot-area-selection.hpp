#pragma once

#include <X11/Xlib.h>

class AreaSelect
{

private:
    Display* display;
    Window root;

    int* getMousePos(int* mousePos);

public:
    AreaSelect();
    ~AreaSelect();
    int* getAreaSelection(int* area);

};
