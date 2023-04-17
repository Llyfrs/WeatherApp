//
// Created by llyfr on 17.4.23.
//

#include "GeoAPI.h"

#include <utility>

API::GeoAPI::GeoAPI(std::string key) :key(std::move(key)) {}

Location API::GeoAPI::getLocation(std::string searchedLocation) {


    // Spaces are not allowed in an url, but they can be represented with dashes (-)
    std::replace(searchedLocation.begin(),searchedLocation.end(), ' ', '-');


    std::string url = "https://api.openweathermap.org/geo/1.0/direct?q=" + searchedLocation + "&appid=" + this->key;

    auto locations = API::makeAPIcall(url)[0];


    // TODO Make sure the returned value is correct, and not empty

    Location location;

    location.lat = locations.at("lat").get<double>();
    location.lon = locations.at("lon").get<double>();
    location.country = locations.at("country").get<std::string>();
    location.name = locations.at("name").get<std::string>();
    location.name = locations.value("state", "N/A");

    return location;
}


nlohmann::json API::makeAPIcall(const std::string& url) {

    std::ostringstream os;
    os << curlpp::options::Url(url);

    std::string string = os.str();

    auto data = nlohmann::json::parse(string);

    return data;

}
