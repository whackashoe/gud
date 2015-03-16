 #if !defined(WEB_REQUEST_H_INCLUDED_)
#define WEB_REQUEST_H_INCLUDED_

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>
#include <web/log.hpp>

namespace web {

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
		GET,
		HEAD,
		PUT,
		POST,
		PATCH,
		DELETE
	};

	static std::map<std::string, request::http_method> methods;

private:
	/**
	 * Line separated raw header.
	 */
	std::vector<std::string> request_lines_;

	std::string method_;
	std::string path_;
	std::map<std::string, std::string> headers_;

public:
	/**
	 * HTTP verb (GET, POST, PATCH, PUT, etc.)
	 */
	std::string const & method_s() const;

	/**
	 * Get method
	 */
	request::http_method method() const;

	/**
	 * Path for this HTTP request. Like:
	 * VERB /path HTTP/6.9
	 */
	std::string const & path() const;

	/**
	 * Construct the request object.
	 *
	 * @param headers Raw HTTP request headers.
	 */
	request(std::string const & headers);

	std::map<std::string, std::string> const & headers() const;
};

} /* /namespace web */

#endif /* WEB_REQUEST_H_INCLUDED_ */
