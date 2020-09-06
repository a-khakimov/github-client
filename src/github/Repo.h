#ifndef REPOINFO_H
#define REPOINFO_H

#include <vector>
#include <string>
#include "../http/Client.h"
#include <nlohmann/json.hpp>

namespace github {

struct Commit {
    std::string author;
    std::string message;
    std::string date;
};

class Repo
{
public:
    Repo();
    explicit Repo(const std::string& reponame);
    virtual ~Repo();
    std::vector<Commit> commits();

private:
    std::string m_reponame;
    http::Client m_client;
    static const std::string githubApiUrl;
};

}

#endif // REPOINFO_H
