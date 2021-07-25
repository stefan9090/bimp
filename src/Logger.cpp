//
// Created by beerd on 7/23/2021.
//

#include "Logger.h"

void Logging::initialize()
{
    auto console = spdlog::stdout_color_mt("console");
    auto console_sink = dynamic_cast<spdlog::sinks::stdout_color_sink_mt *>(
            console->sinks().back().get());
    spdlog::set_default_logger(console);
    spdlog::set_pattern("%^[%H:%M:%S][%-19s:%#][%-5l] %v%$");

#if defined _MSC_VER
    console_sink->set_color(spdlog::level::info, console_sink->WHITE);
#else
    console_sink->set_color(spdlog::level::info, "\033[37m");
#endif
}