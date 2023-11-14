#pragma once

#include <iostream>
#include <X11/Xlib.h>
#include <cairo.h>
#include <cairo-xlib.h>

class Capture
{

private:
    void screenshot();

public:
    Capture();

};
