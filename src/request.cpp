#include <gud/request.hpp>

using namespace gud;

request::request(std::string const & str_req)
{
	std::stringstream ss(str_req);
	std::string line;

	std::stringstream raw_headers_ss;
	std::stringstream raw_body_ss;

	// Status Line
	if(std::getline(ss, line)) {
		std::stringstream ls(line);

		for(auto & m: methods) {
			if(line.find(m.first) == 0) {
				ls >> method_ >> path_;
			}
		}
	}

	// Parse Headers
	while(std::getline(ss, line)) {
		raw_headers_ss << line << "\n";
		std::stringstream ls(line);

		// header lines
		const std::string delimiter = ": ";
		const auto dpos = line.find(delimiter);

		if(dpos != std::string::npos) {
			const std::string field = line.substr(0, dpos);
			const std::string value = (line.length() > dpos+delimiter.size())
				? line.substr(dpos+delimiter.length(), line.length())
				: "";

			headers_[field] = value;
		} else if(line == "\r") {
			// Start of request body
			break;
		} else {
			gud::log::trace("Request header missing delimiter");
		}
	}
	raw_headers_ = raw_headers_ss.str();

	// Parse Body
	while(std::getline(ss, line)) {
		raw_body_ss << line << "\n";
	}
	raw_body_ = raw_body_ss.str();

	if (method_.empty()) {
		gud::log::trace("Found no HTTP method in the request!");
	}
}

std::map<std::string, request::http_method> request::methods = {
	{ "GET",     http_method::GET },
	{ "HEAD",    http_method::HEAD },
	{ "OPTIONS", http_method::OPTIONS },
	{ "TRACE",   http_method::TRACE },
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

std::string const & request::raw_headers() const
{
	return raw_headers_;
}

std::string const & request::raw_body() const
{
	return raw_body_;
}