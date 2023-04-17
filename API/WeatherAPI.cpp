//
// Created by llyfr on 3/27/23.
//

#include "WeatherAPI.h"
#include <utility>

// Creates new API object with its own Key
// We are initializing location to fake information in case user forget to set it up
API::WeatherAPI::WeatherAPI(std::string key): key(std::move(key)), location(0,0,"N/A", "N/A", "N/A") {}

API::WeatherAPI::WeatherAPI(std::string key, Location location) : key(std::move(key)), location(std::move(location)) {}

Forecast API::WeatherAPI::getForecast() {

    std::string url = "https://api.openweathermap.org/data/3.0/onecall?lat=" + std::to_string(this->location.lat) + "&lon=" + std::to_string(this->location.lon) + "&units=metric&appid=" + this->key;

    auto data = API::makeAPIcall(url);


    // TODO check for errors in reply and return false if any is detected

    return Forecast(data);
}




/*nlohmann::json API::WeatherAPI::getData() {
    return this->json_data;
}

*//**
 * Return n-th day prediction \n
 * n == 0 returns current weather information's
 * If out of index throws error
 * **//*
json API::WeatherAPI::getDayData(int n) {

    json day;

    if(n == 0) {
        day = this->json_data.at("current");
    } else {
        day = this->json_data.at("daily")[n-1];
    }

    if(not day.is_null()) {
        return day;
    }

    throw std::out_of_range("Index out of range");

}*/

/*std::vector<nlohmann::json> API::WeatherAPI::getLocations(std::string searchedLocation, int limit = 3) {


    // Spaces are not allowed in an url, but they can be represented with dashes (-)
    std::replace(searchedLocation.begin(),searchedLocation.end(), ' ', '-');


    std::string url = "https://api.openweathermap.org/geo/1.0/direct?q=" + searchedLocation + "&limit=" + std::to_string(limit) + "&appid=" + this->key;

    auto locations = API::WeatherAPI::makeAPIcall(url);

    // TODO Make sure the returned value is correct, and not empty

    std::vector<json> result;
    for(const auto& location : locations ){
        result.push_back(location);
    }

    return result;
}*/



void API::WeatherAPI::setLocation(Location loc) {
    this->location = loc;
}

Location API::WeatherAPI::getLocation() {
    return this->location;
}


