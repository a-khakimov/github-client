// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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
