#include <web/request.hpp>

using namespace web;

request::request(std::string const & headers)
{
	std::stringstream ss(headers);
	std::string line;

	while (std::getline(ss, line)) {
		for(auto & i : methods) {
			if(line.find(i.first) == 0) {
				std::stringstream ss(line);
				ss >> method_ >> path_;
			}
		}
	}

	if (method_.empty()) {
		web::log::trace("Found no HTTP method in the request!");
	}
}

std::map<std::string, request::http_method> request::methods = {
	{ "GET",     http_method::GET },
	{ "HEAD",    http_method::HEAD },
	{ "OPTIONS", http_method::OPTIONS },
	{ "PUT",     http_method::PUT },
	{ "PATCH",   http_method::PATCH },
	{ "POST",    http_method::POST },
	{ "DELETE",  http_method::DELETE },
};

std::string const & request::method_s() const
{
	return method_;
}

std::string const & request::path() const
{
	return path_;
}

request::http_method request::method() const
{
	auto method_it = methods.find(method_);

	if(method_it == methods.end()) {
		return request::http_method::UNKNOWN;
	}

	return method_it->second;
}

std::map<std::string, std::string> const & request::headers() const
{
	return headers_;
}