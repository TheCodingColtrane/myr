#include "curl/curl.h"
#include <string>
#include <iostream>
#include <simdjson.h>


size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}


std::string get(std::string& uri){
    CURL* client = curl_easy_init();
    CURLcode curl_res_code; 
    std::string response;
    if(client){ 
        curl_easy_setopt(client, CURLOPT_URL, uri.c_str());
        curl_easy_setopt(client, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(client, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(client, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36");

        curl_res_code = curl_easy_perform(client);
        if(curl_res_code != CURLE_OK){
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curl_res_code) << std::endl;
        }
        curl_easy_cleanup(client);
        return response;
    }

    return "";
}