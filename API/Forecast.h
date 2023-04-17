//
// Created by llyfr on 17.4.23.
//
#include <nlohmann/json.hpp>


/*
 * Class used to parse data from json format to solid data types.
 * */
class Forecast {
private:
    nlohmann::json data;
public:
    explicit Forecast(nlohmann::json data);
};
