#include "capture.hpp"
#include <iostream>

Capture::Capture()
{
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        std::cout << "Display could not be retrieved..." << std::endl;
        exit(1);
    }
    root = XDefaultRootWindow(display);
    visual = XDefaultVisual(display, XDefaultScreen(display));
}

Capture::~Capture()
{
    XCloseDisplay(display);
}

void Capture::screenshotRegion(int x, int y, int w, int h, std::filesystem::path path)
{

    cairo_surface_t* surface = cairo_xlib_surface_create(display,
                                                        root,
                                                        visual,
                                                        w,
                                                        h);

    cairo_surface_write_to_png(surface, path.filename().string().c_str());

    cairo_surface_destroy(surface);
}

void Capture::screenshot()
{
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, root, &windowAttributes);

    screenshotRegion(0, 0, windowAttributes.width, windowAttributes.height, screenshotPath);
}

void Capture::screenshot(int x, int y, int w, int h)
{
    XWindowChanges xwc;
    xwc.x = x;
    xwc.y = y;
    xwc.width = w;
    xwc.height = h;
    XConfigureWindow(display, root, CWX | CWY | CWWidth | CWHeight, &xwc);

    screenshotRegion(x, y, w, h, screenshotPath);
}

void Capture::screenshot(int w, int h)
{
    XWindowChanges xwc;
    xwc.width = w;
    xwc.height = h;
    XConfigureWindow(display, root, CWWidth | CWHeight, &xwc);

    screenshotRegion(0, 0, w, h, screenshotPath);
}
