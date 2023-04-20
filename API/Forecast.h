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

    std::vector<nlohmann::json> days;

public:
    explicit Forecast(nlohmann::json data);

    size_t getForecastedDaysCount();

    int getTemperature(unsigned int = 0);
    int getHumidity(unsigned int = 0);
    int getPressure(unsigned int = 0);
    int getFeelsLikeTemperature(unsigned int = 0);
    int getUVI(unsigned  int = 0);

    double getWindSpeed(unsigned int = 0);
    double getWindGust(unsigned int = 0);
    int getWindDegree(unsigned int = 0);

};
