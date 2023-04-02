//
// Created by llyfr on 3/27/23.
//

#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace API {

    class WeatherAPI {
    private:
        nlohmann::json json_data;
        std::string key;
        double lat;
        double lon;

        static json makeAPIcall(const std::string& url);

    public:

        explicit WeatherAPI(std::string key);

        void setLocation(double, double);

        bool update();
        json getData();
        json getDayData(int n);

        std::vector<json> getLocations(std::string, int);

    };

}

