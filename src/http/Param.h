#ifndef PARAM_H
#define PARAM_H

#include <string>

namespace http {

class Param {
public:
    Param(const std::string& key, const std::string& value);
    Param(std::string&& key, std::string&& value);
    std::string key() const noexcept;
    std::string value() const noexcept;

private:
    std::string m_key;
    std::string m_value;
};

}

#endif // PARAM_H
