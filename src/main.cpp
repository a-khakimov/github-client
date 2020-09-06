#include <curl/curl.h>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include "http/Client.h"
#include "github/Repo.h"

//curl -X GET "https://api.github.com/repos/curl/curl/commits?page=3&sha=master&since=2020-08-01T00:00:00Z"

int main()
{

    auto now = std::chrono::system_clock::now();
    auto nextWeek = now - std::chrono::hours(24 * 7);
    std::time_t nextWeek_time_t = std::chrono::system_clock::to_time_t(nextWeek);
    std::cout << nextWeek_time_t << "\n";
    char buf[sizeof "0000-00-00T00:00:00Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&nextWeek_time_t));
    std::cout << buf << "\n";

    github::Repo repo("curl");
    repo.commits();

    //http::Client client;
    //const char* url = "https://api.github.com/repos/curl/curl/commits?page=1&sha=master&since=2020-09-01T00:00:00Z";
    //client.doGet(url);
    //http::Response response = client.doGet(url, {http::Param("page", "1"), http::Param("sha", "master")});
    //http::Response response2 = client.doGet(url, {http::Param("page", "1"), http::Param("sha", "master")});

/*
    CURL* curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.47.1");

        std::string response_string;
        std::string header_string;

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        CURLcode res = curl_easy_perform(curl);
        std::cout << "CURLcode: " << res << std::endl;
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);

        nlohmann::json j = nlohmann::json::parse(response_string);

        //std::cout << response_string;
        std::cout << "j.empty = " << j.empty() << std::endl;
        for (auto i : j) {
            const std::string author = i["commit"]["author"]["name"];
            //const std::string committer = i["commit"]["committer"]["name"];
            const std::string date = i["commit"]["author"]["date"];
            const std::string message = i["commit"]["message"];
            std::cout << date << "\t" << author << "\t"  << std::endl;
        }
    }
    */
    return 0;

}
