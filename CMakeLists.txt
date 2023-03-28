cmake_minimum_required(VERSION 3.25)
project(WeatherApp)

set(CMAKE_CXX_STANDARD 17)

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)
pkg_check_modules(NLOHMANN REQUIRED nlohmann_json)


add_executable(WeatherApp main.cpp API/WeatherAPI.cpp API/WeatherAPI.h)
target_link_libraries(WeatherApp ${CURLPP_LDFLAGS})
target_link_libraries(WeatherApp ${NLOHMANN_LDFLAGS})