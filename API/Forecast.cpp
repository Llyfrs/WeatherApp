//
// Created by llyfr on 17.4.23.
//

#include "Forecast.h"
#include <utility>


#include "iostream"

Forecast::Forecast(nlohmann::json data): data(std::move(data)) {

    this->days.push_back(this->data.at("current"));

    for(const auto& day : this->data.at("daily")){
        this->days.push_back(day);
    }

}
/**
 * @param n - witch days you want temperature form, if not specified defaults to 0 returning temperature for current day
 * @return int - representing current temperature
 * */
int Forecast::getTemperature(unsigned int n /*= 0*/) {
    return (n == 0) ? this->days[n].at("temp").get<int>() : this->days[n].at("temp").at("day").get<int>();
}

size_t Forecast::getForecastedDaysCount() {
    return this->days.size();
}

int Forecast::getFeelsLikeTemperature(unsigned int n /*= 0*/) {
    return (n == 0) ? this->days[n].at("feels_like").get<int>() : this->days[n].at("feels_like").at("day").get<int>();
}

int Forecast::getPressure(unsigned int n /*= 0*/) {
    return this->days[n].at("pressure").get<int>();
}

int Forecast::getHumidity(unsigned int n /*= 0*/) {
    return this->days[n].at("humidity").get<int>();
}

int Forecast::getUVI(unsigned int n /*= 0*/) {
    return this->days[n].at("uvi").get<int>();
}

double Forecast::getWindSpeed(unsigned int n) {
    return this->days[n].at("wind_speed").get<double>();
}

double Forecast::getWindGust(unsigned int n) {
    return this->days[n].at("wind_gust").get<double>();
}

int Forecast::getWindDegree(unsigned int n) {
    return this->days[n].at("wind_deg").get<int>();
}



/*
 *
 *
lat Geographical coordinates of the location (latitude)
lon Geographical coordinates of the location (longitude)
timezone Timezone name for the requested location
timezone_offset Shift in seconds from UTC
current Current weather data API response
current.dt Current time, Unix, UTC
current.sunrise Sunrise time, Unix, UTC
current.sunset Sunset time, Unix, UTC
current.temp Temperature. Units - default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
current.feels_like Temperature. This temperature parameter accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
current.pressure Atmospheric pressure on the sea level, hPa
current.humidity Humidity, %
current.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
current.clouds Cloudiness, %
current.uvi Current UV index
current.visibility Average visibility, metres. The maximum value of the visibility is 10km
current.wind_speed Wind speed. Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
current.wind_gust (where available) Wind gust. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
current.wind_deg Wind direction, degrees (meteorological)
current.rain
current.rain.1h (where available) Precipitation, mm/h
current.snow
current.snow.1h (where available) Precipitation, mm/h
current.weather
current.weather.id Weather condition id
current.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
current.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
current.weather.icon Weather icon id. How to get icons
minutely Minute forecast weather data API response
minutely.dt Time of the forecasted data, unix, UTC
minutely.precipitation Precipitation, mm/h
hourly Hourly forecast weather data API response
hourly.dt Time of the forecasted data, Unix, UTC
hourly.temp Temperature. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
hourly.feels_like Temperature. This accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
hourly.pressure Atmospheric pressure on the sea level, hPa
hourly.humidity Humidity, %
hourly.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
hourly.uvi UV index
hourly.clouds Cloudiness, %
hourly.visibility Average visibility, metres. The maximum value of the visibility is 10km
hourly.wind_speed Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour.How to change units used
hourly.wind_gust (where available) Wind gust. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
chourly.wind_deg Wind direction, degrees (meteorological)
hourly.pop Probability of precipitation. The values of the parameter vary between 0 and 1, where 0 is equal to 0%, 1 is equal to 100%
hourly.rain
hourly.rain.1h (where available) Precipitation, mm/h
hourly.snow
hourly.snow.1h (where available) Precipitation, mm/h
hourly.weather
hourly.weather.id Weather condition id
hourly.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
hourly.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
hourly.weather.icon Weather icon id. How to get icons
daily Daily forecast weather data API response
daily.dt Time of the forecasted data, Unix, UTC
daily.sunrise Sunrise time, Unix, UTC
daily.sunset Sunset time, Unix, UTC
daily.moonrise The time of when the moon rises for this day, Unix, UTC
daily.moonset The time of when the moon sets for this day, Unix, UTC
daily.moon_phase Moon phase. 0 and 1 are 'new moon', 0.25 is 'first quarter moon', 0.5 is 'full moon' and 0.75 is 'last quarter moon'. The periods in between are called 'waxing crescent', 'waxing gibous', 'waning gibous', and 'waning crescent', respectively.
daily.temp Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
daily.temp.morn Morning temperature.
daily.temp.day Day temperature.
daily.temp.eve Evening temperature.
daily.temp.night Night temperature.
daily.temp.min Min daily temperature.
daily.temp.max Max daily temperature.
daily.feels_like This accounts for the human perception of weather. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit. How to change units used
daily.feels_like.morn Morning temperature.
daily.feels_like.day Day temperature.
daily.feels_like.eve Evening temperature.
daily.feels_like.night Night temperature.
daily.pressure Atmospheric pressure on the sea level, hPa
daily.humidity Humidity, %
daily.dew_point Atmospheric temperature (varying according to pressure and humidity) below which water droplets begin to condense and dew can form. Units – default: kelvin, metric: Celsius, imperial: Fahrenheit.
daily.wind_speed Wind speed. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
daily.wind_gust (where available) Wind gust. Units – default: metre/sec, metric: metre/sec, imperial: miles/hour. How to change units used
daily.wind_deg Wind direction, degrees (meteorological)
daily.clouds Cloudiness, %
daily.uvi The maximum value of UV index for the day
daily.pop Probability of precipitation. The values of the parameter vary between 0 and 1, where 0 is equal to 0%, 1 is equal to 100%
daily.rain (where available) Precipitation volume, mm
daily.snow (where available) Snow volume, mm
daily.weather
daily.weather.id Weather condition id
daily.weather.main Group of weather parameters (Rain, Snow, Extreme etc.)
daily.weather.description Weather condition within the group (full list of weather conditions). Get the output in your language
daily.weather.icon Weather icon id. How to get icons
alerts National weather alerts data from major national weather warning systems
alerts.sender_name Name of the alert source. Please read here the full list of alert sources
alerts.event Alert event name
alerts.start Date and time of the start of the alert, Unix, UTC
alerts.end Date and time of the end of the alert, Unix, UTC
alerts.description Description of the alert
alerts.tags Type of severe weather
 *
 * */