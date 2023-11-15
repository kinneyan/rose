#include "capture.hpp"

Capture::Capture()
{
    screenshot();
}

void Capture::screenshot()
{
    Display* display;
    Window root;
    cairo_surface_t* surface;

    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        std::cout << "Display could not be retrieved..." << std::endl;
        exit(1);
    }

    root = XDefaultRootWindow(display);

    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, root, &windowAttributes);

    Visual* visual = XDefaultVisual(display, XDefaultScreen(display));

    surface = cairo_xlib_surface_create(display, root, visual, windowAttributes.width, windowAttributes.height);

    cairo_surface_write_to_png(surface, "screenshot.png");

    cairo_surface_destroy(surface);
    XCloseDisplay(display);
}
