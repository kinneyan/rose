#include "screenshot-area-selection.hpp"

#include <iostream>

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
    XGrabButton(display, Button1, AnyModifier, root, true, ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None);

    XEvent event;
    bool buttonPressed = false;
    bool waitingForRelease = false;

    int initialX, initialY;
    int finalX, finalY;

    while (!buttonPressed || waitingForRelease)
    {
        XNextEvent(display, &event);

        switch (event.type)
        {
            case ButtonPress:
                if (event.xbutton.button == Button1 && !buttonPressed)
                {
                    buttonPressed = true;
                    waitingForRelease = true;
                    int pos[2];
                    getMousePos(pos);
                    initialX = pos[0];
                    initialY = pos[1];
                }
                break;
            case ButtonRelease:
                if (event.xbutton.button == Button1 && buttonPressed)
                {
                    waitingForRelease = false;
                    int pos[2];
                    getMousePos(pos);
                    finalX = pos[0];
                    finalY = pos[1];
                }
            default:
                break;
        }
    }

    std::cout << '(' << initialX << ',' << initialY << ')' << '\n';
    std::cout << '(' << finalX << ',' << finalY << ')' << '\n';

    // calculate rect dimensions
    // return rect dimensions

}
