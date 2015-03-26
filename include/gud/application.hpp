#if !defined(GUD_APPLICATION_H_INCLUDED_)
#define GUD_APPLICATION_H_INCLUDED_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cerrno>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <gud/request.hpp>
#include <gud/response.hpp>
#include <gud/exceptions.hpp>
#include <gud/log.hpp>
#include <gud/db.hpp>
#include <gud/util.hpp>

namespace gud {

/**
 * Main application logic class.
 * Non-copyable.
 */
class application
{
public:
	// Public types

	/**
	 * All the views should be of this type.
	 */
	typedef std::function<std::string(request &, response &)> view_function_t;
private:
	std::vector<std::string> args_;

	/**
	 * method->view map type (a better indexing?)
	 */
	typedef std::map<request::http_method, view_function_t> method_map_t;

	/**
	 * path->mapped methods type
	 */
	typedef std::map<std::string, method_map_t> view_map_t;

	/**
	 * Map of views.
	 */
	view_map_t views_;

	/**
	 * Server socket file descriptor.
	 */
	int server_socket_;

	/**
	 * Initialize all systems with config
	 */
	void bootup();

	/**
	 * Generate formatted string compliant with rfc1123
	 * For Date header
	 */
	std::string rfc1123_datetime(time_t time);
public:
	application(application const &) = delete;
	application & operator=(application const &) = delete;

	/**
	 * Application constructor.
	 *
	 * @param argc Argument count.
	 * @param argv Argument values.
	 */
	application(int argc, char * argv[]);

	/**
	 * Args getter.
	 */
	std::vector<std::string> const & args() const;

	/**
	 * Get all app routes.
	 */
	view_map_t const & routes() const;

	/**
	 * Mount a GET view at `path` to `view`.
	 * @param method (GET, POST, ...)
	 * @param path Path.
	 * @param view View function.
	 */
	void mount_route(request::http_method method, std::string const & path, view_function_t view);

	/**
	 * Convenient shortcut for mounting OPTIONS view.
	 * @param path Path.
	 * @param view View function.
	 */
	void options(std::string const & path, view_function_t view);

	/**
	 * Convenient shortcut for mounting GET view.
	 * @param path Path.
	 * @param view View function.
	 */
	void get(std::string const & path, view_function_t view);

	/**
	 * Convenient shortcut for mounting PUT view.
	 * @param path Path.
	 * @param view View function.
	 */
	void put(std::string const & path, view_function_t view);

	/**
	 * Convenient shortcut for mounting PATCH view.
	 * @param path Path.
	 * @param view View function.
	 */
	void patch(std::string const & path, view_function_t view);

	/**
	 * Convenient shortcut for mounting GET view.
	 * @param path Path.
	 * @param view View function.
	 */
	void post(std::string const & path, view_function_t view);

	/**
	 * Convenient shortcut for mounting DELETE view.
	 * @param path Path.
	 * @param view View function.
	 */
	void delete_(std::string const & path, view_function_t view);

	/**
	 * Convenient shortcut for mounting wildcard view.
	 * @param path Path.
	 * @param view View function.
	 */
	void all(std::string const & path, view_function_t view);

	/**
	 * Get view function for a route.
	 * Match method and path to a view, then return it.
	 *
	 * @param method HTTP method (GET, POST, etc.)
	 * @param path View path.
	 */
	view_function_t get_route(request::http_method method, std::string const & path);

	/**
	 * Process a request and return response. Does not throw.
	 *
	 * @param req A request instance with headers specified.
	 * @param res A response instance
	 * @return A valid HTTP response.
	 */
	std::string process(request & req, response & res) throw();

	/**
	 * Run very simple HTTP server to process remote requests.
	 *
	 * @param port Port number (0-65535)
	 * @param address Address (default is 127.0.0.1)
	 */
	void listen(unsigned short const port, const char * address = "127.0.0.1");
};

} /* /namespace gud */

#endif /* GUD_APPLICATION_H_INCLUDED_ */

