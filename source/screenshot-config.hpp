#pragma once

class ScreenshotConfig
{
    bool takeFullScreenShot;
    bool takeAreaShot;
    bool uploadFile = true;

private:

public:
    ScreenshotConfig();
    bool getTakeFullScreenShot();
    void setTakeFullScreenShot(bool fullShot);
    bool getTakeAreaShot();
    void setTakeAreaShot(bool areaShot);
    bool getUploadFile(); 
    void setUploadFile(bool upload);

};
