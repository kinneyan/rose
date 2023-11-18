#pragma once

#include <filesystem>

class ScreenshotConfig
{

private:
    bool takeFullScreenShot;
    bool takeAreaShot;
    bool uploadFile = true;

    std::filesystem::path programDir;
    std::filesystem::path saveDir;
    std::filesystem::path file;
    std::filesystem::path fileType;

    char* host;
    char* apiKey;

    bool createProgramData();

public:
    ScreenshotConfig();
    bool getTakeFullScreenShot();
    void setTakeFullScreenShot(bool fullShot);
    bool getTakeAreaShot();
    void setTakeAreaShot(bool areaShot);
    bool getUploadFile();
    void setUploadFile(bool upload);

};
