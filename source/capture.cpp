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

void screenshot(int x, int y, int w, int h)
{
    screenshot_region(x, y, w, h, screenshotPath);
}
