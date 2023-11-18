#include "screenshot-area-selection.hpp"

#include <X11/keysym.h>

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

int* AreaSelect::formatCoords(int* coords, int* dimensions)
{
    if (coords[0] < coords[2])
    {
        dimensions[0] = coords[0];
        dimensions[2] = coords[2] - coords[0];
    }
    else
    {
        dimensions[0] = coords[2];
        dimensions[2] = coords[0] - coords[2];
    }

    if (coords[1] < coords[3])
    {
        dimensions[1] = coords[1];
        dimensions[3] = coords[3] - coords[1];
    }
    else
    {
        dimensions[1] = coords[3];
        dimensions[3] = coords[1] - coords[3];
    }

    return dimensions;
}

int* AreaSelect::getAreaSelection(int* dimensions)
{
    XEvent event;
    bool buttonPressed = false;
    bool waitingForRelease = false;
    bool escape = false;
    int coords[4];

    // grab mouse button
    XGrabButton(display, Button1, AnyModifier, root, true, ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None);
    // grab escape key to cancel selection
    XGrabKey(display, XKeysymToKeycode(display, XK_Escape), AnyModifier, root, true, GrabModeAsync, GrabModeAsync);

    while ((!buttonPressed || waitingForRelease) && !escape)
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
                    coords[0] = pos[0];
                    coords[1] = pos[1];
                }
                break;
            case ButtonRelease:
                if (event.xbutton.button == Button1 && buttonPressed)
                {
                    waitingForRelease = false;
                    int pos[2];
                    getMousePos(pos);
                    coords[2] = pos[0];
                    coords[3] = pos[1];
                }
            case KeyPress:
                if (XLookupKeysym(&event.xkey, 0) == XK_Escape)
                    escape = true;
                break;
            default:
                break;
        }

        if (escape)
            return NULL;
    }

    return formatCoords(coords, dimensions);
}
