#if !defined(WEB_RESPONSE_H_INCLUDED_)
#define WEB_RESPONSE_H_INCLUDED_

#include <string>
#include <map>
#include <sstream>

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


	void add_header(std::string const & field, std::string const & value);

	std::map<std::string, std::string> const & headers() const;
};

} /* /namespace web */

#endif /* WEB_RESPONSE_H_INCLUDED_ */