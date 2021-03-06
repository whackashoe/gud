#include <gud/config.hpp>

using namespace gud;

gud::json config::settings_ = {
    { "server", {
        { "port", 3333 },
        { "name", "gud" },
        { "host", "127.0.0.1" },
        { "allow_trace", true }
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
        }},
        { "db", {
            { "connect", true },
            { "host", "127.0.0.1" },
            { "port", 3306 },
            { "username", "root" },
            { "password", "" },
            { "database", "gud" }
        }}
    }}
};

gud::json config::get(std::string const & field)
{
    std::vector<std::string> tokens = util::undot(field);

    gud::json * it = &settings_;
    for(size_t i=0; i < tokens.size(); ++i) {
        if(it->find(tokens[i]) != it->end()) {
            it = &(*it)[tokens[i]];
        } else {
            throw std::runtime_error("gud::config::get has nothing set here: " + field);
        }
    }

    return *it;
}

void config::publish(std::string const & field, gud::json conf)
{
    std::vector<std::string> tokens = util::undot(field);

    gud::json * it = &settings_;
    for(size_t i=0; i < tokens.size() - 1; ++i) {
        if(! (it->find(tokens[i]) != it->end())) {
            (*it)[tokens[i]] = json::object();
        }

        it = &(*it)[tokens[i]];
    }

    (*it)[tokens[tokens.size() - 1]] = conf;
}