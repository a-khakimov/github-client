// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Param.h"

namespace http {


Param::Param(const std::string &key, const std::string &value)
    : m_key(key), m_value(value)
{

}

Param::Param(std::string &&key, std::string &&value)
    : m_key(std::move(key)), m_value(std::move(value))
{

}

std::string Param::key() const noexcept
{
    return m_key;
}

std::string Param::value() const noexcept
{
    return m_value;
}

}
