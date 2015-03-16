#include <web/config.hpp>

using namespace web;

web::json config::settings_ = {
    { "server", {
        { "port", 3333 },
        { "name", "web" },
        { "host", "127.0.0.1" }
    }},
    { "app", {
        { "debug", true },
        { "timezone", "UTC" },
        { "paths", {
            { "root", "/var/www" },
            { "views", "/resources/views/" }
        }},
        { "log", {
            { "format", "%+" },
            { "level", "debug" }
        }}
    }}
};

web::json config::get(std::string const & field)
{
    std::vector<std::string> tokens;
    boost::split(tokens, field, boost::is_any_of("."), boost::token_compress_on);

    web::json * it = &settings_;
    for(size_t i=0; i < tokens.size(); ++i) {
        if(it->find(tokens[i]) != it->end()) {
            it = &(*it)[tokens[i]];
        } else {
            throw std::runtime_error("web::config::get has nothing set here: " + field);
        }
    }

    return *it;
}

void config::publish(std::string const & field, web::json conf)
{
    std::vector<std::string> tokens;
    boost::split(tokens, field, boost::is_any_of("."), boost::token_compress_on);

    web::json * it = &settings_;
    for(size_t i=0; i < tokens.size() - 1; ++i) {
        if(! (it->find(tokens[i]) != it->end())) {
            (*it)[tokens[i]] = json::object();
        }

        it = &(*it)[tokens[i]];
    }

    (*it)[tokens[tokens.size() - 1]] = conf;
}