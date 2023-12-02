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

    // create settings config
    configFile = programDir / "settings.cfg";
    if (!std::filesystem::exists(configFile))
    {
        std::ofstream settingsFile(configFile.c_str());
        settingsFile.close();

        // no host information available because we are manually creating the config file
        // so no upload is possible
        uploadFile = false;
    }

    // read config file
    config.readFile(configFile.c_str());
    readConfigFile();

    // create screenshots directory
    if (saveDir == "")
    {
        saveDir = programDir;
        saveDir.operator/=("screenshots/");
        if (!std::filesystem::is_directory(saveDir))
        {
            std::filesystem::create_directory(saveDir);
        }
    }

    if (fileType == "")
    {
        fileType = ".png";
    }

    return true;
}

void ScreenshotConfig::initializeConfigFile()
{
    libconfig::Setting &root = config.getRoot();

    // create any needed categories
    if (!root.exists("upload"))
    {
        root.add("upload", libconfig::Setting::TypeGroup);
    }

    // check if host category exists
    libconfig::Setting &upload = root["upload"];
    if (!upload.exists("host"))
    {
        upload.add("host", libconfig::Setting::TypeGroup);
    }

    // check if url entry exists
    libconfig::Setting &host = upload["host"];
    if (!host.exists("url"))
    {
        host.add("url", libconfig::Setting::TypeString) = "";
    }

    if (!host.exists("arguments"))
    {
        host.add("arguments", libconfig::Setting::TypeGroup);
    }

    if (!root.exists("file"))
    {
        root.add("file", libconfig::Setting::TypeGroup);
    }

    libconfig::Setting &file = root["file"];
    // check for a custom save directory
    if (!file.exists("save-directory"))
    {
        file.add("save-directory", libconfig::Setting::TypeString) = "";
    }

    // check for an alternate file type
    if (!file.exists("ext"))
    {
        file.add("ext", libconfig::Setting::TypeString) = "";
    }
}

void ScreenshotConfig::readConfigFile()
{
    initializeConfigFile();

    libconfig::Setting &host = config.getRoot()["upload"]["host"];

    hostURL = (const char*) host.lookup("url");

    // read any arguments provided
    libconfig::Setting &argsSetting = host["arguments"];
    int i = 0;
    bool exitNow = false;
    while (!exitNow)
    {
        try
        {
            libconfig::Setting &setting = argsSetting[i];
            args[setting.getName()] = (std::string) setting;
            ++i;
        }
        catch (...)
        {
            exitNow = true;
        }
    }

    libconfig::Setting &file = config.getRoot()["file"];
    saveDir = file.lookup("save-directory");
    fileType = file.lookup("ext");
}

void ScreenshotConfig::writeConfigFile()
{
    initializeConfigFile();

    libconfig::Setting &host = config.getRoot()["upload"]["host"];

    // write the host url
    libconfig::Setting &url = host.lookup("url");
    url = hostURL.c_str();

    // write args
    libconfig::Setting &argsSetting = host["arguments"];
    for (std::map<std::string, std::string>::iterator i = args.begin(); i != args.end(); i++)
    {
        if (!argsSetting.exists(i->first))
        {
            argsSetting.add(i->first, libconfig::Setting::TypeString);
        }
        libconfig::Setting &setting = argsSetting.lookup(i->first);
        setting = i->second;
    }

    libconfig::Setting &file = config.getRoot()["file"];

    // write the save directory
    libconfig::Setting &save_directory = file.lookup("save-directory");
    save_directory = saveDir;

    // write the file extension
    libconfig::Setting &ext = file.lookup("ext");
    ext = fileType;

    config.writeFile(configFile.c_str());
}

ScreenshotConfig::~ScreenshotConfig()
{
    writeConfigFile();
}

bool ScreenshotConfig::getTakeFullScreenShot() { return takeFullScreenShot; }
void ScreenshotConfig::setTakeFullScreenShot(bool fullShot) { takeFullScreenShot = fullShot;}
bool ScreenshotConfig::getTakeAreaShot() { return takeAreaShot; }
void ScreenshotConfig::setTakeAreaShot(bool areaShot) { takeAreaShot = areaShot; }
bool ScreenshotConfig::getUploadFile() { return uploadFile; }
void ScreenshotConfig::setUploadFile(bool upload) { uploadFile = upload; }
std::filesystem::path ScreenshotConfig::getProgramDir() { return programDir; }
void ScreenshotConfig::setProgramDir(std::filesystem::path dir) { programDir = dir; }
std::filesystem::path ScreenshotConfig::getSaveDir() { return saveDir; }
void ScreenshotConfig::setSaveDir(std::filesystem::path dir) { saveDir = dir; }
std::filesystem::path ScreenshotConfig::getFileName() { return file; }
void ScreenshotConfig::setFileName(std::filesystem::path name) { file = name; }
std::filesystem::path ScreenshotConfig::getFileType() { return fileType; }
void ScreenshotConfig::setFileType(std::filesystem::path type) { fileType = type; }
std::string ScreenshotConfig::getHostURL() { return hostURL; }
std::map<std::string, std::string> ScreenshotConfig::getArgs() { return args; }
