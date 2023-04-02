#include "API/WeatherAPI.h"
#include "API/GeoAPI.h"
#include <iostream>
#include <sstream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>


int main() {

    API::WeatherAPI weatherAPI("c37fc2bf45a37a8ff187e0955ee2e5ef");

    weatherAPI.update();

    auto json = weatherAPI.getData();


    std::cout << json.at("hourly").size();

    nlohmann::json sunrise = json["current"];
    std::cout << weatherAPI.getDayData(0).at("temp") << std::endl;


    return 0;
}
