//
// Created by fredrik on 2019-03-19.
//
#include "CurlFirebase.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <string>
#include <functional>
#include <curl/curl.h>

CurlFirebase::CurlFirebase(const std::string Url, const std::string token) :
    url(Url), access_token(token){;}


void CurlFirebase::notify(const std::string &data) {
#ifdef DEBUGMODE
    std::cout << "url: " << url << " access_token: " << access_token << std::endl;
    std::cout << "CurlFirebase::notify: " << data << std::endl;
#endif

    auto curl = curl_easy_init();
    struct curl_slist *headers= nullptr;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    std::string token_header = "access_token: " + access_token;
    headers = curl_slist_append(headers, token_header.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

    std::string json("{\"time\": ");
    auto now = std::chrono::system_clock::now();
    auto unixtime = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    json.append("\"").append(std::to_string(unixtime)).append("\",").append(" \"temp\" : \"").append(data).append("\"}");

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up) {
    std::string data;

    for (int i = 0; i<size*nmemb; i++)
    {
        data.push_back(buf[i]);
    }

    /**
     * @todo prase for "404"in data
     */
#ifdef DEBUGMODE
    std::cout << "return: " << data << std::endl;
#endif

    return size*nmemb;
}
