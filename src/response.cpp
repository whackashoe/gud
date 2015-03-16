#include <web/response.hpp>

using namespace web;

response::response()
{
	add_header("Content-Type", "text/html; charset=UTF-8");
    add_header("Server", web::config::get("server.name"));
    status_code_ = 200;
}

response::~response()
{
	//
}

std::map<unsigned int, std::string> response::status_codes = {
    { 100, "Continue" },
    { 101, "Switching Protocols" },
    { 200, "OK" },
    { 201, "Created" },
    { 202, "Accepted" },
    { 203, "Non-Authoritative Information" },
    { 204, "No Content" },
    { 205, "Reset Content" },
    { 206, "Partial Content" },
    { 300, "Multiple Choices" },
    { 301, "Moved Permanently" },
    { 302, "Found" },
    { 303, "See Other" },
    { 304, "Not Modified" },
    { 305, "Use Proxy" },
    { 307, "Temporary Redirect" },
    { 400, "Bad Request" },
    { 401, "Unauthorized" },
    { 402, "Payment Required" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
    { 405, "Method Not Allowed" },
    { 406, "Not Acceptable" },
    { 407, "Proxy Authentication Required" },
    { 408, "Request Timeout" },
    { 409, "Conflict" },
    { 410, "Gone" },
    { 411, "Length Required" },
    { 412, "Precondition Failed" },
    { 413, "Request Entity Too Large" },
    { 414, "Request-URI Too Long" },
    { 415, "Unsupported Media Type" },
    { 416, "Requested Range Not Satisfiable" },
    { 417, "Expectation Failed" },
    { 500, "Internal Server Error" },
    { 501, "Not Implemented" },
    { 502, "Bad Gateway" },
    { 503, "Service Unavailable" },
    { 504, "Gateway Timeout" },
    { 505, "HTTP Version Not Supported" }
};

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

void response::set_status_code(const unsigned int status)
{
    status_code_ = status;
}

unsigned int response::status_code()
{
    return status_code_;
}