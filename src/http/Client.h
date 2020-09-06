#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <curl/curl.h>

namespace http {

class Param {
public:
    Param(const std::string& key, const std::string& value)
        : m_key(key), m_value(value) {}

    Param(std::string&& key, std::string&& value)
        : m_key(std::move(key)), m_value(std::move(value)) {}

    std::string key() const noexcept
    {
        return m_key;
    }
    std::string value() const noexcept
    {
        return m_value;
    }
private:
    std::string m_key;
    std::string m_value;
};

struct Response {
    Response() : code(-1) {}
    long code;
    std::string header;
    std::string content;
};

class Client
{
public:
    Client();
    virtual ~Client();
    Response doGet(const std::string& url, const std::initializer_list<Param>& params = {});

private:
    CURL* m_curl;
    std::string makeFullUrl(const std::string& url, const std::initializer_list<Param>& params = {});
};

}

#endif // HTTPCLIENT_H
