#pragma once

#include <X11/Xlib.h>
#include <filesystem>

class Capture
{

private:
    Display* display;
    Window root;
    Visual* visual;
    std::filesystem::path screenshotPath;
    std::filesystem::path fileType;

    void buildPath();
    void screenshotRegion(int x, int y, int w, int h);

public:
    Capture();
    ~Capture();

    void screenshot();
    void screenshot(int x, int y, int w, int h);
    void screenshot(int w, int h);

};
