#include "capture.hpp"

Capture::Capture()
{
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        std::cout << "Failed to get display" << std::endl;
        exit(1);
    }
}

Capture::~Capture()
{
    XCloseDisplay(display);
}
