//
// Created by llyfr on 3/27/23.
//
#pragma once
#include <string>

#include "Forecast.h"
#include "GeoAPI.h"

namespace API {

    class WeatherAPI {
    private:
        std::string key;
        Location location;

    public:

        explicit WeatherAPI(std::string key);
        WeatherAPI(std::string key, Location location);

        Forecast getForecast();
        void setLocation(Location);
        Location getLocation();

    };

}

