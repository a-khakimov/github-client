#include "Repo.h"
#include <iostream>
#include <chrono>

namespace github {

Repo::Repo()
{

}

Repo::Repo(const std::string& owner, const std::string& name)
    : m_owner(owner), m_name(name)
{

}

Repo::~Repo()
{

}

/* Elapsed time in ISO 8601 format */
std::string Repo::elapsedTime(const elapsedTime_t time)
{
    size_t hours = 0;
    switch (time) {
    case lastDay:
        hours = 24;
        break;
    case lastWeek:
        hours = 24 * 7;
        break;
    case lastMonth:
        hours = 24 * 30;
        break;
    default:
        hours = 24; // default 24 hours
        break;
    }
    const auto now = std::chrono::system_clock::now();
    const auto lastHours = now - std::chrono::hours(hours);
    const std::time_t delta = std::chrono::system_clock::to_time_t(lastHours);
    char buf[sizeof "0000-00-00T00:00:00Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&delta));
    return std::string(buf);
}

std::vector<Commit> Repo::commits(const elapsedTime_t time)
{
    const std::string url = githubApiUrl + m_owner + "/" + m_name + "/commits?";
    const std::string elapsedtime = elapsedTime(time);
    std::vector<Commit> commits;
    int page = 0;

    while (true)
    {
        page++;

        http::Response response = m_client.doGet(url, {
                http::Param("page", std::to_string(page)),
                http::Param("sha", "master"),
                http::Param("since", elapsedtime)
            }
        );

        if (response.code != 200) {
            throw; // FIXME: gihub exception
        }

        nlohmann::json j = nlohmann::json::parse(response.content);

        std::cout << ".";
        if (j.empty()) {
            break;
        }

        for (const auto& i : j) {
            Commit commit;
            commit.author = i["commit"]["author"]["name"];
            commit.date = i["commit"]["author"]["date"];
            commit.message = i["commit"]["message"];
            commits.push_back(commit);
        }
    }

    std::cout << "." << std::endl;

    return commits;
}

std::string Repo::description()
{
    std::string result;
    const std::string url = githubApiUrl + m_owner + "/" + m_name;
    http::Response response = m_client.doGet(url);
    if (response.code != 200) {
        throw; // FIXME: gihub exception
    }
    nlohmann::json j = nlohmann::json::parse(response.content);
    if (not j.empty()) {
        result += j.value("description", "");
    }
    return result;
}

const std::string Repo::githubApiUrl = "https://api.github.com/repos/";

}

