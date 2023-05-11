#include "API/WeatherAPI.h"
#include <iostream>
#include <sstream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include "curlpp/Easy.hpp"
#include <nlohmann/json.hpp>
#include <QListView>
#include <QPushButton>
#include <QApplication>
#include <fstream>
#include "GUI/mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    MainWindow w;

    w.show();


    auto geoAPI = API::GeoAPI("c37fc2bf45a37a8ff187e0955ee2e5ef");
    Location loc = geoAPI.getLocation("Nový Jičín");


    auto API = API::WeatherAPI("c37fc2bf45a37a8ff187e0955ee2e5ef",loc);

    auto forecast = API.getForecast();

    forecast.getHourlyForecast();

    std::cout << forecast.getHourlyForecast().temperature << std::endl;
    std::cout << forecast.getDailyForecast(1).temperature.day << std::endl;




    std::cout << forecast.getWindSpeed() << std::endl;

    std::cout << forecast.getWeather().icon << std::endl;

    return QApplication::exec();
}
