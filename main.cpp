#include "API/WeatherAPI.h"
#include <iostream>
#include <sstream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>


int main() {

    API::WeatherAPI weatherAPI("c37fc2bf45a37a8ff187e0955ee2e5ef");

    std::string location;
    std::cout << "Enter your location" << std::endl;
    std::getline(std::cin,location);
    auto locations = weatherAPI.getLocations(location, 6);

    std::cout << "Chose your location:" << std::endl;

    for(int i = 0; i < locations.size(); i++) {
        std::cout << std::to_string(i+1) << ". " << locations[i]["name"].get<std::string>() << ", " << locations[i].at("country").get<std::string>() << std::endl;
    }

    std::cout << "Your input: ";
    int choice = 0;
    std::cin >> choice;
    choice--;
    weatherAPI.setLocation(locations[choice]["lat"].get<double>() , locations[choice]["lon"].get<double>());
    weatherAPI.update();

    auto data = weatherAPI.getDayData(0);


    std::cout << "Today's temperature is: " + std::to_string(data["temp"].get<int>()) + "°C";

    return 0;
}
