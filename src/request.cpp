#include <web/request.hpp>

using namespace web;

request::request(std::string const & headers)
{
	std::stringstream ss(headers);
	std::string line;

	for(int i=0; std::getline(ss, line); ++i) {
		std::stringstream ls(line);

		if(i == 0) {
			// status line

			for(auto & m: methods) {
				if(line.find(m.first) == 0) {
					ls >> method_ >> path_;
				}
			}
		} else {
			// header lines
			const std::string delimiter = ": ";
			const auto dpos = line.find(delimiter);
			if(dpos != std::string::npos) {
				const std::string field = line.substr(0, dpos);
				const std::string value = (line.length() > dpos+delimiter.size())
					? line.substr(dpos+delimiter.length(), line.length())
					: "";

				headers_[field] = value;
			} else {
				web::log::trace("Request header missing delimiter");
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