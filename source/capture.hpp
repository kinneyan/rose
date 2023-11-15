#pragma once

#include <X11/Xlib.h>
#include <cairo-xlib.h>

class Capture
{

private:
    Display* display;
    Window root;
    Visual* visual;

    void screenshotRegion(int x, int y, int w, int h, char* fname);

public:
    Capture();
    ~Capture();

    void screenshot();
    void screenshot(int x, int y, int w, int h);
    void screenshot(int w, int h);

};
