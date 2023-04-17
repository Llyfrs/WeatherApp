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


    std::cout << loc.name << " : " << loc.country << "cords: " << loc.lat <<", " << loc.lon << std::endl;

    return QApplication::exec();
}
