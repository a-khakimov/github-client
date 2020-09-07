cmake_minimum_required(VERSION 3.5)

project(github-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(github-client
    src/main.cpp
    src/http/Client.cpp
    src/http/Param.cpp
    src/github/Repo.cpp
)

#find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(github-client -lcurl)
