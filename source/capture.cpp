#include "capture.hpp"

Capture::Capture()
{
    display = gdk_display_open(NULL);
    if (display == NULL)
    {
        std::cout << "Failed to get display." << std::endl;
        exit(1);
    }
}

Capture::~Capture()
{
    gdk_display_close(display);
}
