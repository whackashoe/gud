#if !defined(GUD_RESPONSE_H_INCLUDED_)
#define GUD_RESPONSE_H_INCLUDED_

#include <string>
#include <map>
#include <sstream>
#include <gud/config.hpp>
#include <gud/util.hpp>

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
	 * All stored headers
	 */
	std::map<std::string, std::string> headers_;

	/**
	 * Raw text of headers
	 */
	std::string raw_headers_;

	/**
	 * Raw text of body
	 */
	std::string raw_body_;

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
	 * Append a header to the response
	 */
	void add_header(std::string const & field, std::string const & value);

	/**
	 * Get a map of all request headers
	 */
	std::map<std::string, std::string> const & headers() const;

	/**
	 * Get raw headers as string
	 */
	std::string const raw_headers() const;

	/**
	 * Get raw body as string
	 */
	std::string const raw_body() const;

	/**
	 * Set raw body as string
	 */
	void set_raw_body(std::string const & body);

	/**
	 * Get the status code
	 */
	unsigned int status_code();

	/**
	 * Set the status code for response
	 */
	void set_status_code(const unsigned int);
};

} /* /namespace gud */

#endif /* GUD_RESPONSE_H_INCLUDED_ */