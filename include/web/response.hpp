#if !defined(WEB_RESPONSE_H_INCLUDED_)
#define WEB_RESPONSE_H_INCLUDED_

#include <string>
#include <map>
#include <sstream>
#include <web/config.hpp>

namespace web {

/**
 * HTTP response.
 */
class response
{
private:
	/**
	 * Buffered data written from view.
	 */
	std::stringstream stream_;

	/**
	 * All stored headers
	 */
	std::map<std::string, std::string> headers_;
public:
	/**
	 * Constructor of HTTP response.
	 */
	response();

	/**
	 * All buffered data is written to the client_socket_ descriptor.
	 */
	~response();

	/**
	 * A reference to view's stream.
	 */
	std::stringstream & stream();


	/**
	 * Append a header to the response
	 */
	void add_header(std::string const & field, std::string const & value);

	/**
	 * Get a map of all request headers
	 */
	std::map<std::string, std::string> const & headers() const;
};

} /* /namespace web */

#endif /* WEB_RESPONSE_H_INCLUDED_ */