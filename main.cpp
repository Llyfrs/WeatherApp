#include <iostream>
#include <sstream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>


int main() {

    curlpp::Cleanup myCleanup;

// Send request and get a result.
// Here I use a shortcut to get it in a string stream ...

    std::ostringstream os;
    os << curlpp::options::Url(std::string("https://api.openweathermap.org/data/3.0/onecall?lat=33.44&lon=-94.04&appid=c37fc2bf45a37a8ff187e0955ee2e5ef"));

    std::string asAskedInQuestion = os.str();
    std::cout << asAskedInQuestion << std::endl;

    auto json = nlohmann::json::parse(asAskedInQuestion);


    nlohmann::json sunrise = json["current"];
    std::cout << sunrise["sunrise"] << std::endl;

    return 0;
}
