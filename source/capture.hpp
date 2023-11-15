#pragma once

#include <X11/Xlib.h>
#include <cairo-xlib.h>
#include <filesystem>

class Capture
{

private:
    Display* display;
    Window root;
    Visual* visual;
    std::filesystem::path screenshotPath = "screenshots/";
    std::filesystem::path fileType = ".png";

    std::filesystem::path buildPath();
    void screenshotRegion(int x, int y, int w, int h, std::filesystem::path path);

public:
    Capture();
    ~Capture();

    void screenshot();
    void screenshot(int x, int y, int w, int h);
    void screenshot(int w, int h);

};
