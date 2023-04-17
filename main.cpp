#include "API/WeatherAPI.h"
#include <iostream>
#include <sstream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>
#include <QListView>
#include <QPushButton>
#include <QApplication>
#include "GUI/mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    MainWindow w;

    w.show();


    auto geoAPI = API::GeoAPI("c37fc2bf45a37a8ff187e0955ee2e5ef");
    Location loc = geoAPI.getLocation("Nový Jičín");


    auto API = API::WeatherAPI("c37fc2bf45a37a8ff187e0955ee2e5ef",loc);

    auto forecast = API.getForecast();


    std::cout << forecast.getTemperature();




    return QApplication::exec();
}
