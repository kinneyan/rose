#pragma once

#include "screenshot-config.hpp"

class Rose
{

private:
    ScreenshotConfig screenshotConfig;

    int readOptions(int argc, char** argv);

public:
    Rose();
    int run(int argc, char** argv);

};
