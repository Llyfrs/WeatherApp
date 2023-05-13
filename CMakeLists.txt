cmake_minimum_required(VERSION 3.25)
project(WeatherApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)
pkg_check_modules(NLOHMANN REQUIRED nlohmann_json)
pkg_check_modules(QT6 REQUIRED Qt6Widgets)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(COPY icons DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(WeatherApp main.cpp API/GeoAPI.cpp API/GeoAPI.h API/WeatherAPI.cpp API/WeatherAPI.h GUI/mainwindow.cpp GUI/mainwindow.h API/Forecast.cpp API/Forecast.h GUI/settingwindow.cpp GUI/settingwindow.h GUI/settingwindow.ui  GUI/MyFrame.hpp)
target_link_libraries(WeatherApp ${CURLPP_LDFLAGS})
target_link_libraries(WeatherApp ${NLOHMANN_LDFLAGS})
target_link_libraries(WeatherApp
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )