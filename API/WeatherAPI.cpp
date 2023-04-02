//
// Created by llyfr on 3/27/23.
//

#include "WeatherAPI.h"

#include <utility>

// Creates new API object with its own Key
API::WeatherAPI::WeatherAPI(std::string key): key(std::move(key)), json_data(nlohmann::detail::value_t::null) {}

bool API::WeatherAPI::update() {

    std::ostringstream os;
    os << curlpp::options::Url(("https://api.openweathermap.org/data/3.0/onecall?lat=33.44&lon=-94.04&units=metric&appid=" + this->key));

    std::string asAskedInQuestion = os.str();
    std::cout << asAskedInQuestion << std::endl;

    this->json_data = nlohmann::json::parse(asAskedInQuestion);

    return true;
}


nlohmann::json API::WeatherAPI::getData() {
    return this->json_data;
}

/**
 * Return n-th day prediction \n
 * n == 0 returns current weather information's
 * If out of index throws error
 * **/
nlohmann::json API::WeatherAPI::getDayData(int n) {

    nlohmann::json day;

    if(n == 0) {
        day = this->json_data.at("current");
    } else {
        day = this->json_data.at("daily")[n-1];
    }

    if(not day.is_null()) {
        return day;
    }

    throw std::out_of_range("Index out of range, ");

}
