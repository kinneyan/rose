#ifndef CAPTURE_HPP
#define CAPTURE_HPP

#include <iostream>
#include <gdk/gdk.h>

class Capture
{

private:
    GdkDisplay* display;

public:
    Capture();
    ~Capture();
    
};

#endif
