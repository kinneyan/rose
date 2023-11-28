#include "rose.hpp"
#include "screenshot-capture.hpp"
#include "screenshot-area-selection.hpp"
#include "file-upload.hpp"

#include <iostream>
#include <unistd.h>

Rose::Rose()
{
    screenshotConfig.setTakeFullScreenShot(true);
    screenshotConfig.setTakeAreaShot(false);
    screenshotConfig.setUploadFile(true);
}

int Rose::run(int argc, char**argv)
{
    if (readOptions(argc, argv) != 0)
        return 1;

    Capture capture(screenshotConfig.getSaveDir(), screenshotConfig.getFileType());

    std::filesystem::path file = "";

    if (screenshotConfig.getTakeFullScreenShot())
    {
        file = capture.screenshot();
    }
    else if (screenshotConfig.getTakeAreaShot())
    {
        int dimensions[4];
        AreaSelect select;
        if (select.getAreaSelection(dimensions) == NULL)
            return 0;
        file = capture.screenshot(dimensions[0], dimensions[1], dimensions[2], dimensions[3]);
    }

    if (file != "")
    {
        screenshotConfig.setFileName(file);
    }

    if (screenshotConfig.getUploadFile())
    {
        Connection host(screenshotConfig.getHostURL(), screenshotConfig.getArgs());
        host.uploadFile(screenshotConfig.getFileName().string().c_str());
    }

    screenshotConfig.setFileName(file);

    return 0;
}

int Rose::readOptions(int argc, char** argv)
{
    int c;

    while ((c = getopt(argc, argv, "fal")) != -1)
    {
        switch (c)
        {
            case 'f':
                screenshotConfig.setTakeFullScreenShot(true);
                screenshotConfig.setTakeAreaShot(false);
                break;
            case 'a':
                screenshotConfig.setTakeAreaShot(true);
                screenshotConfig.setTakeFullScreenShot(false);
                break;
            case 'l':
                screenshotConfig.setUploadFile(false);
                break;
            case '?':
                std::cerr << "Program terminated." << std::endl;
                return 1;
            default:
                break;
        }
    }
    return 0;
}
