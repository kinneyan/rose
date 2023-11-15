class Rose
{

private:
    bool fullScreen;
    bool areaSelection;
    bool noUpload;

    void readOptions(int argc, char** argv);

public:
    Rose();
    int run(int argc, char** argv);

};
