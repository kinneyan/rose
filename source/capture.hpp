#pragma once

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
