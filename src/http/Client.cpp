#include "Client.h"
#include <iostream>

namespace http {

static size_t writeCallback(void *contents, const size_t size, const size_t nmemb, void *userp)
{
    const size_t real_size = size * nmemb;
    static_cast<std::string*>(userp)->append(
                static_cast<char*>(contents),
                real_size);
    return real_size;
}

Client::Client()
{
    m_curl = curl_easy_init();
}

Client::~Client()
{
    curl_easy_cleanup(m_curl);
}

Response Client::doGet(const std::string &url, const std::initializer_list<Param> &params)
{
    Response response;
    const std::string fullUrl = makeFullUrl(url, params);
    //std::cout << "fullUrl=" << fullUrl << std::endl;

    if (m_curl != nullptr) {
        curl_easy_setopt(m_curl, CURLOPT_URL, fullUrl.c_str());
        curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "curl/7.47.1");
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response.content);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &response.header);
        curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, writeCallback);

        CURLcode res = curl_easy_perform(m_curl);
        if (res == CURLE_OK) {
            curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &response.code);
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
    }
    return response;
}

std::string Client::makeFullUrl(const std::string &url, const std::initializer_list<Param> &params)
{
    std::string fullUrl { url };
    for (const auto& param : params) {
        fullUrl += param.key() + "=" + param.value() + "&";
    }
    return fullUrl;
}


}
