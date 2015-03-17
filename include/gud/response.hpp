#if !defined(GUD_RESPONSE_H_INCLUDED_)
#define GUD_RESPONSE_H_INCLUDED_

#include <string>
#include <map>
#include <sstream>
#include <gud/config.hpp>

namespace gud {

/**
 * HTTP response.
 */
class response
{
public:
	static std::map<unsigned int, std::string> status_codes;
private:
	/**
	 * Buffered data written from view.
	 */
	std::stringstream stream_;

	/**
	 * All stored headers
	 */
	std::map<std::string, std::string> headers_;

	/**
	 * HTTP Status Code
	 */
	unsigned int status_code_;
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

	/**
	 * Set the status code for response
	 */
	void set_status_code(const unsigned int);

	/**
	 * Get the status code
	 */
	unsigned int status_code();
};

} /* /namespace gud */

#endif /* GUD_RESPONSE_H_INCLUDED_ */