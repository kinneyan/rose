#pragma once

class ScreenshotConfig
{

private:
    bool takeFullScreenShot;
    bool takeAreaShot;
    bool uploadFile = true;

public:
    ScreenshotConfig();
    bool getTakeFullScreenShot();
    void setTakeFullScreenShot(bool fullShot);
    bool getTakeAreaShot();
    void setTakeAreaShot(bool areaShot);
    bool getUploadFile();
    void setUploadFile(bool upload);

};
