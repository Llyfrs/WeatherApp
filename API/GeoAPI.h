//
// Created by llyfr on 17.4.23.
//

#pragma once

#include <string>
#include <utility>
#include <vector>
#include "nlohmann/json.hpp"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>



struct Location {
    double lat;
    double lon;
    std::string country;
    std::string name;
    std::string state;

    Location(double lat, double lon, std::string country, std::string name, std::string state)
            :lat(lat), lon(lon), country(std::move(country)), name(std::move(name)), state(std::move(state)) {};

    Location(): lat(0), lon(0), country("N/A"), name("N/A") {}

};


namespace API {

    nlohmann::json makeAPIcall(const std::string& url);

    std::stringstream getImageFromUrl(const std::string& url);

    class GeoAPI {

    private:
        std::string key;

    public:
        GeoAPI() = default;
        explicit GeoAPI(std::string key);

        Location getLocation(const std::string&);
        Location getLocation(double, double);

        std::vector<Location> getLocations(double, double, int );
        std::vector<Location> getLocations(const std::string&, int);

        bool testAPIkey();

    };
}


