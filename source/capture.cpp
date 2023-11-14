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

    root = DefaultRootWindow(display);

    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, root, &windowAttributes);
    //std::cout << windowAttributes.width << 'x' << windowAttributes.height << std::endl;

    Visual* visual = DefaultVisual(display, DefaultScreen(display));

    //XImage* image = XGetImage(display, root, 0, 0, windowAttributes.width, windowAttributes.height, AllPlanes, ZPixmap);
    surface = cairo_xlib_surface_create(display, root, visual, windowAttributes.width, windowAttributes.height);

    cairo_surface_write_to_png(surface, "screenshot.png");

    cairo_surface_destroy(surface);
    XCloseDisplay(display);
}
