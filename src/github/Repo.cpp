#include "Repo.h"
#include <iostream>
#include <chrono>

namespace github {

Repo::Repo()
{

}

Repo::Repo(const std::string &reponame) : m_reponame(reponame)
{

}

Repo::~Repo()
{

}

std::vector<Commit> Repo::commits()
{
    std::vector<Commit> commits;
    const std::string url = githubApiUrl + m_reponame + "/" + m_reponame + "/commits?";
    http::Response response = m_client.doGet(url, {
            http::Param("page", "1"),
            http::Param("sha", "master")
        }
    );
    if (response.code != 200) {
        throw;
    }

    nlohmann::json j = nlohmann::json::parse(response.content);

    std::cout << "j.empty = " << j.empty() << std::endl;
    for (const auto& i : j) {
        Commit commit;
        commit.author = i["commit"]["author"]["name"];
        //const std::string committer = i["commit"]["committer"]["name"];
        commit.date = i["commit"]["author"]["date"];
        std::string message = i["commit"]["message"];
        message.resize(30);
        std::remove_if(message.begin(), message.end(), [](const char c) {
            return (c == '\n' or c == '\t' or c == '\r' or c == '\0');
        });
        std::cout << commit.date << "\t" << commit.author << " \t" << message  << std::endl;
        commits.push_back(commit);
    }
    return commits;
}

const std::string Repo::githubApiUrl = "https://api.github.com/repos/";

}

