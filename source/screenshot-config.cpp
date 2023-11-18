#include "screenshot-config.hpp"

#include <iostream>
#include <cstdlib>

ScreenshotConfig::ScreenshotConfig()
{
    takeFullScreenShot = false;
    takeAreaShot = false;
    uploadFile = false;

    if (!createProgramData())
        exit(1);
    // create dot directory in home dir to store config and
    // screenshots

}

bool ScreenshotConfig::createProgramData()
{

    char* home = std::getenv("HOME");
    if (home == NULL)
    {
        std::cout << "Failed to find home directory." << std::endl;
        return false;
    }

    programDir = home;
    programDir.operator/=(".rose");

    if (!std::filesystem::is_directory(programDir))
    {
        std::filesystem::create_directory(programDir);
    }

    saveDir = programDir;
    saveDir.operator/=("screenshots/");
    if (!std::filesystem::is_directory(saveDir))
    {
        std::filesystem::create_directory(saveDir);
    }

    return true;
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
