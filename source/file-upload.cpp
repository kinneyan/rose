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

size_t Connection::curlWriteFunction(char* ptr, size_t size, size_t nmemb, std::string* userData)
{
    size_t nlength = size * nmemb;
    userData->append((char*) ptr, nlength);
    return nlength;
}

int Connection::uploadFile(const char* fpath)
{
    std::string response;
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

    // don't return ok if curl failed
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    // use write callback function to response string instead of
    // printing the output
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode responseCode = curl_easy_perform(curl);

    curl_mime_free(form);

    //std::cerr << curl_easy_strerror(response) << std::endl;
    //std::cout << response << std::endl;

    return responseCode;
}
