#include "screenshot-config.hpp"

#include <iostream>
#include <cstdlib>
#include <fstream>

ScreenshotConfig::ScreenshotConfig()
{
    takeFullScreenShot = false;
    takeAreaShot = false;
    uploadFile = false;

    if (!createProgramData())
        exit(1);

}

bool ScreenshotConfig::createProgramData()
{

    char* home = std::getenv("HOME");
    if (home == NULL)
    {
        std::cerr << "Failed to find home directory." << std::endl;
        return false;
    }

    // create dot directory
    programDir = home;
    programDir.operator/=(".rose");

    if (!std::filesystem::is_directory(programDir))
    {
        std::filesystem::create_directory(programDir);
    }

    // create screenshots directory
    saveDir = programDir;
    saveDir.operator/=("screenshots/");
    if (!std::filesystem::is_directory(saveDir))
    {
        std::filesystem::create_directory(saveDir);
    }

    fileType = ".png";

    // create settings config
    configFile = programDir / "settings.cfg";
    if (!std::filesystem::exists(configFile))
    {
        std::ofstream settingsFile(configFile.c_str());
        settingsFile.close();
    }
    readConfigFile();


    return true;
}

void ScreenshotConfig::readConfigFile()
{
    config.readFile(configFile.c_str());

    // read image settings
    libconfig::Setting &root = config.getRoot();

    // create any needed categories
    if (!root.exists("upload"))
    {
        root.add("upload", libconfig::Setting::TypeGroup);
    }

    if (!root.exists("file"))
    {
        root.add("file", libconfig::Setting::TypeGroup);
    }

}

void ScreenshotConfig::writeConfigFile()
{
    config.writeFile(configFile.c_str());
}

ScreenshotConfig::~ScreenshotConfig()
{
    writeConfigFile();
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

std::filesystem::path ScreenshotConfig::getProgramDir()
{
    return programDir;
}

void ScreenshotConfig::setProgramDir(std::filesystem::path dir)
{
    programDir = dir;
}

std::filesystem::path ScreenshotConfig::getSaveDir()
{
    return saveDir;
}

void ScreenshotConfig::setSaveDir(std::filesystem::path dir)
{
    saveDir = dir;
}

std::filesystem::path ScreenshotConfig::getFileName()
{
    return file;
}

void ScreenshotConfig::setFileName(std::filesystem::path name)
{
    file = name;
}

std::filesystem::path ScreenshotConfig::getFileType()
{
    return fileType;
}

void ScreenshotConfig::setFileType(std::filesystem::path type)
{
    fileType = type;
}
