#ifndef CAPTURE_HPP
#define CAPTURE_HPP

#include <X11/Xlib.h>
#include <iostream>

class Capture
{

private:
    Display* display;

public:
    Capture()
    {
        display = XOpenDisplay(NULL);
        if (display == NULL)
        {
            std::cout << "Failed to get display" << std::endl;
            exit(1);
        }
    }

};

#endif
