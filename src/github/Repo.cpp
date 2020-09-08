// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Repo.h"
#include <iostream>
#include <chrono>

namespace github {

Repo::Repo(const std::string& owner, const std::string& name)
    : m_owner(owner), m_name(name)
{
    getStringRepoAttr();
}

Repo::~Repo()
{

}

/* Elapsed time in ISO 8601 format */
std::string Repo::elapsedTime(const RangeOfCommits range)
{
    size_t hours = 0;
    switch (range) {
    case forLastDay:
        hours = 24;
        break;
    case forLastWeek:
        hours = 24 * 7;
        break;
    case forLastMonth:
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

Commits Repo::commits(const RangeOfCommits range)
{
    const std::string url = githubApiUrl + m_owner + "/" + m_name + "/commits?";
    const std::string elapsedtime = elapsedTime(range);
    std::vector<Commit> commits;
    int page = 0;

    while (true)
    {
        page++;
        http::Response response = m_client.doGet(url, {
            http::Param("page", std::to_string(page)),
            http::Param("sha", "master"),
            http::Param("since", elapsedtime)
        });

        if (response.code != 200) {
            throw Exception("Bad response code - " + std::to_string(response.code));
        }

        try {
            nlohmann::json j = nlohmann::json::parse(response.content);
            if (j.empty() or not j.is_array()) {
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
        catch (std::exception& e) {
            throw Exception("commits() Content parsing error");
        }
    }

    return commits;
}

std::string Repo::fullname() const noexcept
{
    return m_repoAttributes.fullname;
}

std::string Repo::description() const noexcept
{
    return m_repoAttributes.description;
}

std::string Repo::homepage() const noexcept
{
    return m_repoAttributes.homepage;
}

std::string Repo::languages() const noexcept
{
    return m_repoAttributes.languages;
}

std::string Repo::giturl() const noexcept
{
    return m_repoAttributes.giturl;
}

std::string Repo::createdDate() const noexcept
{
    return m_repoAttributes.createdDate;
}

std::string Repo::updatedDate() const noexcept
{
    return m_repoAttributes.updatedDate;
}

void Repo::getStringRepoAttr()
{
    const std::string url = githubApiUrl + m_owner + "/" + m_name;
    http::Response response = m_client.doGet(url);
    if (response.code != 200) {
        throw Exception("Bad response code - " + std::to_string(response.code));
    }
    try {
        nlohmann::json j = nlohmann::json::parse(response.content);
        if (not j.empty() and not j.is_null()) {
            nlohmann::json jattrVal = j["homepage"];
            m_repoAttributes.homepage = jattrVal.is_string() ? jattrVal : "";
            jattrVal = j["full_name"];
            m_repoAttributes.fullname = jattrVal.is_string() ? jattrVal : "";
            jattrVal = j["git_url"];
            m_repoAttributes.giturl = jattrVal.is_string() ? jattrVal : "";
            jattrVal = j["language"];
            m_repoAttributes.languages = jattrVal.is_string() ? jattrVal : "";
            jattrVal = j["description"];
            m_repoAttributes.description = jattrVal.is_string() ? jattrVal : "";
            jattrVal = j["created_at"];
            m_repoAttributes.createdDate = jattrVal.is_string() ? jattrVal : "";
            jattrVal = j["updated_at"];
            m_repoAttributes.updatedDate = jattrVal.is_string() ? jattrVal : "";
        }
    }
    catch (std::exception& e) {
        throw Exception("getStringRepoAttr() Content parsing error");
    }
}

const std::string Repo::githubApiUrl = "https://api.github.com/repos/";

}

