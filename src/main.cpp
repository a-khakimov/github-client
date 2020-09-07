#include <iostream>
#include <getopt.h>
#include <iomanip>
#include "github/Repo.h"

void usage(const std::string& prog)
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << prog << std::endl << "Arguments:" << std::endl;
    std::cout << "\t -h  Help" << std::endl;
    std::cout << "\t -r  <repo>" << std::endl;
    std::cout << "\t -o  <owner>" << std::endl;
    std::cout << "\t -c  Print commits for last [day]|[week]|[month]" << std::endl;
    std::cout << "\t -i  Print repo information" << std::endl;
}

void printCommits(const github::Commits& commits)
{
    std::cout << "--------------- Commits -------------------" << std::endl;
    std::cout << std::setw(20) << "Date"
              << std::setw(22) << "Author"
              << "   Message" << std::endl;
    for (auto commit : commits) {
        std::remove_if(commit.message.rbegin(), commit.message.rend(), [](char c) {
            return (not std::isprint(c) or std::iscntrl(c));
        });

        commit.message.resize(60);
        std::cout << commit.date << "  " << std::setw(20)
                << commit.author << " [ "
                << commit.message << " ... ]" << std::endl;
    }
    std::cout << "--------------- Commits -------------------" << std::endl;
}

void printRepoInfo(const github::Repo& repo)
{
    std::cout << "Full name: " << repo.fullname() << std::endl;
    std::cout << "Homepage: " << repo.homepage() << std::endl;
    std::cout << "Url: " << repo.giturl() << std::endl;
    std::cout << "Languages: " << repo.languages() << std::endl;
    std::cout << "Created: " << repo.createdDate() << std::endl;
    std::cout << "Updated: " << repo.updatedDate() << std::endl;
    std::cout << "Description: " << repo.description() << std::endl;
}

int main(int argc, char** argv)
{
    std::string repo_name;
    std::string owner;
    std::string commit_arg;
    int doPrintRepoInfo = 0;

    int opt;
    while ((opt = getopt(argc, argv, "r:o:c:ih")) != -1){
        switch (opt) {
        case 'r':
            repo_name = optarg;
            break;
        case 'o':
            owner = optarg;
            break;
        case 'c':
            commit_arg = optarg;
            break;
        case 'i':
            ++doPrintRepoInfo;
            break;
        case 'h':
            usage(argv[0]);
            return EXIT_SUCCESS;
        default:
            break;
        };
    };

    if (repo_name.empty() or owner.empty()) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    try {
        github::Repo repo(owner, repo_name);
        if (doPrintRepoInfo) {
            printRepoInfo(repo);
        }
        if (not commit_arg.empty()) {
            github::RangeOfCommits range;
            if (commit_arg == "day") {
                range = github::forLastDay;
            } else if (commit_arg == "week") {
                range = github::forLastWeek;
            } else if (commit_arg == "month") {
                range = github::forLastMonth;
            } else {
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            github::Commits commits = repo.commits(range);
            printCommits(commits);
        }
    }
    catch (github::Exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
