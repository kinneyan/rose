#include "capture.hpp"

#include <cairo-xlib.h>
#include <iostream>
#include <time.h>

Capture::Capture()
{
    display = XOpenDisplay(NULL);
    root = XDefaultRootWindow(display);
    visual = XDefaultVisual(display, XDefaultScreen(display));

    screenshotPath = "screenshots/";
    fileType = ".png";
}

Capture::~Capture()
{
    XCloseDisplay(display);
}

void Capture::buildPath()
{
    std::filesystem::path path;

    time_t currTime = time(NULL);
    static const int bufferSize = 80;
    char buf[bufferSize];
    strftime(buf, bufferSize, "ScreenshotAt-%Y-%m-%d_%H-%M-%S", localtime(&currTime));

    path = buf;
    path.operator+=(fileType);

    screenshotPath.replace_filename(path);
}

void Capture::screenshotRegion(int x, int y, int w, int h)
{
    buildPath();

    if (!std::filesystem::is_directory(screenshotPath.parent_path()))
    {
        std::filesystem::create_directory(screenshotPath.parent_path());
    }

    cairo_surface_t* rawSurface = cairo_xlib_surface_create(display,
                                                            root,
                                                            visual,
                                                            x + w,
                                                            y + h);

    cairo_surface_t* surface = cairo_surface_create_for_rectangle(rawSurface,
                                                                 x,
                                                                 y,
                                                                 w,
                                                                 h);

    cairo_surface_write_to_png(surface, screenshotPath.string().c_str());

    cairo_surface_destroy(rawSurface);
    cairo_surface_destroy(surface);
}

void Capture::screenshot()
{
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, root, &windowAttributes);

    screenshotRegion(0, 0, windowAttributes.width, windowAttributes.height);
}

void Capture::screenshot(int x, int y, int w, int h)
{
    screenshotRegion(x, y, w, h);
}

void Capture::screenshot(int w, int h)
{
    screenshotRegion(0, 0, w, h);
}
