#ifndef REPOINFO_H
#define REPOINFO_H

#include <vector>
#include <string>
#include "../http/Client.h"
#include <nlohmann/json.hpp>

namespace github {

typedef enum {
    lastDay,
    lastWeek,
    lastMonth
} elapsedTime_t;

struct Commit {
    std::string author;
    std::string message;
    std::string date;
};

class Repo
{
public:
    Repo();
    explicit Repo(const std::string& owner, const std::string& name);
    virtual ~Repo();
    std::vector<Commit> commits(const elapsedTime_t time);
    std::string description();

private:
    std::string elapsedTime(const elapsedTime_t time);

    std::string m_owner;
    std::string m_name;
    http::Client m_client;
    static const std::string githubApiUrl;
};

}

#endif // REPOINFO_H
