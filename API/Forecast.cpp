//
// Created by llyfr on 17.4.23.
//

#include "Forecast.h"
#include <utility>

Forecast::Forecast(nlohmann::json data): data(std::move(data)) {}
