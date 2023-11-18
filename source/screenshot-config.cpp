#include "screenshot-config.hpp"

ScreenshotConfig::ScreenshotConfig()
{
    takeFullScreenShot = false;
    takeAreaShot = false;
    uploadFile = false;
}

bool ScreenshotConfig::getTakeFullScreenShot()
{
    return takeFullScreenShot;
}

void ScreenshotConfig::setTakeFullScreenShot(bool fullShot)
{
    takeFullScreenShot = fullShot;
}

bool ScreenshotConfig::getTakeAreaShot()
{
    return takeAreaShot;
}

void ScreenshotConfig::setTakeAreaShot(bool areaShot)
{
    takeAreaShot = areaShot;
}

bool ScreenshotConfig::getUploadFile()
{
    return uploadFile;
}

void ScreenshotConfig::setUploadFile(bool upload)
{
    uploadFile = upload;
}
