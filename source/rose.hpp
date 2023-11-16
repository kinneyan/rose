#pragma once

class Rose
{

private:
    bool fullScreen;
    bool areaSelection;
    bool noUpload;

    int readOptions(int argc, char** argv);

public:
    Rose();
    int run(int argc, char** argv);

};
