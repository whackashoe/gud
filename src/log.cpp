#include <web/log.hpp>

using namespace web;

std::shared_ptr<spdlog::logger> web::log::logger = spdlog::stdout_logger_mt("console");