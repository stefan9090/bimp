//
// Created by beerd on 7/23/2021.
//

#ifndef IMP_BEER_LOGGER_H
#define IMP_BEER_LOGGER_H


#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)

class Logging
{
public:
    static void initialize();
};


#endif //IMP_BEER_LOGGER_H
