#include <gud/log.hpp>

using namespace gud;

std::shared_ptr<spdlog::logger> gud::log::logger = spdlog::stdout_logger_mt("console");

void log::set_level(spdlog::level::level_enum l)
{
    gud::log::logger->set_level(l);
}

void log::set_pattern(std::string const & pattern)
{
    gud::log::logger->set_pattern(pattern);
}