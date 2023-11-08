#pragma once

#include <iostream>
#include <X11/Xlib.h>

class Capture
{

private:
    Display* display;

public:
    Capture();
    ~Capture();


};
