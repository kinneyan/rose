#pragma once

#include <curl/curl.h>

class Connection
{

private:
    CURL* curl;

public:
    Connection();
    ~Connection();

};
