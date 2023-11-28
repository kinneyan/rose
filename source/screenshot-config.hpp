#pragma once

#include <filesystem>
#include <libconfig.h++>
#include <map>

class ScreenshotConfig
{

private:
    libconfig::Config config;

    bool takeFullScreenShot;
    bool takeAreaShot;
    bool uploadFile;

    std::filesystem::path programDir;
    std::filesystem::path configFile;
    std::filesystem::path saveDir;
    std::filesystem::path file;
    std::filesystem::path fileType;

    std::string hostURL;
    std::map<std::string, std::string> args;

    bool createProgramData();
    void initializeConfigFile();
    void readConfigFile();
    void writeConfigFile();

public:
    ScreenshotConfig();
    ~ScreenshotConfig();
    bool getTakeFullScreenShot();
    void setTakeFullScreenShot(bool fullShot);
    bool getTakeAreaShot();
    void setTakeAreaShot(bool areaShot);
    bool getUploadFile();
    void setUploadFile(bool upload);
    std::filesystem::path getProgramDir();
    void setProgramDir(std::filesystem::path dir);
    std::filesystem::path getSaveDir();
    void setSaveDir(std::filesystem::path dir);
    std::filesystem::path getFileName();
    void setFileName(std::filesystem::path name);
    std::filesystem::path getFileType();
    void setFileType(std::filesystem::path type);
    std::string getHostURL();
    std::map<std::string, std::string> getArgs();

};
