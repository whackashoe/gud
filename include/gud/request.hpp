 #if !defined(GUD_REQUEST_H_INCLUDED_)
#define GUD_REQUEST_H_INCLUDED_

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>
#include <gud/log.hpp>

namespace gud {

/**
 * HTTP request class.
 */
class request
{
public:
	/**
	 * Supported verbs.
	 */
	enum class http_method
	{
		UNKNOWN,
		WILDCARD,
		OPTIONS,
		TRACE,
		GET,
		HEAD,
		PUT,
		POST,
		PATCH,
		DELETE
	};

	static std::map<std::string, request::http_method> methods;

private:
	std::string method_;
	std::string path_;
	std::map<std::string, std::string> headers_;
	std::string raw_headers_;
	std::string raw_body_;

public:
	/**
	 * Get method
	 */
	request::http_method method() const;

	/**
	 * Get method string representation
	 */
	std::string const & method_s() const;

	/**
	 * Path for this HTTP request. Like:
	 * VERB /path HTTP/6.9
	 */
	std::string const & path() const;

	/**
	 * Get body of request
	 */
	std::string const & raw_body() const;

	/**
	 * Construct the request object.
	 *
	 * @param headers Raw HTTP request headers.
	 */
	request(std::string const & headers);

	/**
	 * Get a map of all request headers
	 */
	std::map<std::string, std::string> const & headers() const;

	/**
	 * Get raw request headers
	 */
	std::string const & raw_headers() const;
};

} /* /namespace gud */

#endif /* GUD_REQUEST_H_INCLUDED_ */
