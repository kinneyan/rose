#include "rose.hpp"
#include "capture.hpp"

#include <iostream>
#include <unistd.h>

Rose::Rose()
{
    fullScreen = true;
    areaSelection = false;
    noUpload = false;
}

int Rose::run(int argc, char**argv)
{
    if (readOptions(argc, argv) != 0)
        return 1;

    Capture capture;

    if (fullScreen)
    {
        capture.screenshot();
    }

    if (areaSelection)
    {
        //get area selection
        //capture.screenshot(x, y, w, h);
    }
    
    return 0;
}

int Rose::readOptions(int argc, char** argv)
{
    int c;

    while ((c = getopt(argc, argv, "fal")) != -1)
    {
        switch (c)
        {
            case 'f':
                fullScreen = true;
                areaSelection = false;
                break;
            case 'a':
                areaSelection = true;
                fullScreen = false;
                break;
            case 'l':
                noUpload = true;
                break;
            case '?':
                std::cerr << "Program terminated." << std::endl;
                return 1;
            default:
                break;
        }
    }
    return 0;
}
