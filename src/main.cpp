#include <iostream>
#include "http/Client.h"
#include "github/Repo.h"


int main()
{
    //github::Repo repo("a-khakimov", "github-client");
    github::Repo repo("curl", "curl");
    std::cout << repo.description() << std::endl;

    std::vector<github::Commit> commits = repo.commits(github::lastWeek);
    for (auto& commit : commits) {
        commit.message.resize(40);
        std::remove_if(commit.message.begin(), commit.message.end(), [](char c) {
            return (!std::isprint(c));
        });
        commit.message.resize(40);
        std::cout
                << commit.date << " "
                << commit.author << "\t [ "
                << commit.message << " ... ]" << std::endl;
    }

    return 0;

}
