#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

namespace http {

struct Response {
    Response() : code(-1) { }
    long code;
    std::string header;
    std::string content;
};

}

#endif // RESPONSE_H
