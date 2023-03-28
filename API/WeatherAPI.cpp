//
// Created by llyfr on 3/27/23.
//

#include "WeatherAPI.h"

#include <utility>

// Creates new API object with its own Key
API::WeatherAPI::WeatherAPI(std::string key): key(std::move(key)), json_data(nlohmann::detail::value_t::null) {}

bool API::WeatherAPI::update() {

    std::ostringstream os;
    os << curlpp::options::Url(("https://api.openweathermap.org/data/3.0/onecall?lat=33.44&lon=-94.04&appid=" + this->key));

    std::string asAskedInQuestion = os.str();
    std::cout << asAskedInQuestion << std::endl;

    this->json_data = nlohmann::json::parse(asAskedInQuestion);

    return true;
}

nlohmann::json API::WeatherAPI::getData() {
    return this->json_data;
}
