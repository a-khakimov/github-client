#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <curl/curl.h>
#include "Param.h"
#include "Response.h"

namespace http {

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

struct Exception : public std::exception
{
    Exception(const std::string& message)
    {
        m_message = "Http::Client() exception: " + message;
    }
    const char* what() const throw ()
    {
        return m_message.c_str();
    }
    std::string m_message;
};


}

#endif // HTTPCLIENT_H
