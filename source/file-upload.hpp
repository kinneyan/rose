#pragma once

#include <curl/curl.h>
#include <string>
#include <map>

class Connection
{

private:
    CURL* curl;
    std::string hostURL;
    std::map<std::string, std::string> args;

    static size_t curlWriteFunction(char* ptr, size_t size, size_t nmemb, std::string* userData);

public:
    Connection(std::string host, std::map<std::string, std::string> args);
    ~Connection();
    int uploadFile(const char* fpath);

};
