#include <web/log.hpp>

using namespace web;

std::shared_ptr<spdlog::logger> web::log::logger = spdlog::stdout_logger_mt("console");

void log::set_level(spdlog::level::level_enum l)
{
    web::log::logger->set_level(l);
}

void log::set_pattern(std::string const & pattern)
{
    web::log::logger->set_pattern(pattern);
}