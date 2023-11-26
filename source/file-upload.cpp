#include "file-upload.hpp"

#include <iostream>

Connection::Connection()
{
    curl = curl_easy_init();
    if (curl == NULL)
    {
        std::cerr << "CURL could not be initialized. " << std::endl;
        exit(1);
    }
}

Connection::~Connection()
{
    curl_easy_cleanup(curl);
}
