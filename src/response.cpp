#include <web/response.hpp>

using namespace web;

response::response()
{
	add_header("Content-Type", "text/html");
    add_header("Server", web::config::get("server.name"));
}

response::~response()
{
	//
}

std::stringstream & response::stream()
{
	return stream_;
}

void response::add_header(std::string const & field, std::string const & value)
{
    headers_[field] = value;
}

std::map<std::string, std::string> const & response::headers() const
{
    return headers_;
}
