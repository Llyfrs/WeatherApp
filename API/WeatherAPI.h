//
// Created by llyfr on 3/27/23.
//

#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>


namespace API {

    class WeatherAPI {
    private:
        nlohmann::json json_data;
        std::string key;
    public:

        explicit WeatherAPI(std::string key);

        bool update();
        nlohmann::json getData();
        nlohmann::json getDayData(int n);

    };

}

