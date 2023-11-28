#include "file-upload.hpp"

#include <iostream>

Connection::Connection(std::string host, std::map<std::string, std::string> argsMap)
{
    curl = curl_easy_init();
    if (curl == NULL)
    {
        std::cerr << "CURL could not be initialized. " << std::endl;
        exit(1);
    }

    hostURL = host;
    args = argsMap;
}

Connection::~Connection()
{
    curl_easy_cleanup(curl);
}

int Connection::uploadFile(const char* fpath)
{
    curl_easy_setopt(curl, CURLOPT_URL, hostURL.c_str());

    curl_mime* form = curl_mime_init(curl);
    curl_mimepart* field = curl_mime_addpart(form);

    // add args
    for (std::map<std::string, std::string>::iterator i = args.begin(); i != args.end(); i++)
    {
        curl_mime_data(field, i->second.c_str(), CURL_ZERO_TERMINATED);
        curl_mime_name(field, i->first.c_str());
    }

    field = curl_mime_addpart(form);
    curl_mime_filedata(field, fpath);
    curl_mime_name(field, "file");

    curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
    CURLcode response = curl_easy_perform(curl);

    curl_mime_free(form);

    std::cerr << curl_easy_strerror(response) << std::endl;

    return (int) response;
}
