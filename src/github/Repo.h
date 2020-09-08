// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef REPOINFO_H
#define REPOINFO_H

#include <vector>
#include <string>
#include "../http/Client.h"
#include <nlohmann/json.hpp>

namespace github {

typedef enum {
    forLastDay,
    forLastWeek,
    forLastMonth
} RangeOfCommits;

struct Commit {
    std::string author;
    std::string message;
    std::string date;
};

typedef std::vector<github::Commit> Commits;

class Repo
{
public:
    explicit Repo(const std::string& owner, const std::string& name);
    virtual ~Repo();
    Commits commits(const RangeOfCommits range);
    std::string fullname() const noexcept;
    std::string description() const noexcept;
    std::string homepage() const noexcept;
    std::string languages() const noexcept;
    std::string giturl() const noexcept;
    std::string createdDate() const noexcept;
    std::string updatedDate() const noexcept;

private:
    std::string elapsedTime(const RangeOfCommits range);
    void getStringRepoAttr();

    struct RepoAttributes {
        std::string fullname;
        std::string description;
        std::string homepage;
        std::string languages;
        std::string giturl;
        std::string createdDate;
        std::string updatedDate;
    };

    RepoAttributes m_repoAttributes;
    std::string m_owner;
    std::string m_name;
    http::Client m_client;
    static const std::string githubApiUrl;
};

struct Exception : public std::exception
{
    Exception(const std::string& message)
    {
        m_message = "Github::Repo() exception: " + message;
    }
    const char* what() const throw ()
    {
        return m_message.c_str();
    }
    std::string m_message;
};

}

#endif // REPOINFO_H
