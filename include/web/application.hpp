#if !defined(WEB_APPLICATION_H_INCLUDED_)
#define WEB_APPLICATION_H_INCLUDED_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <web/aux/utils.hpp>
#include <web/request.hpp>
#include <web/response.hpp>
#include <web/exceptions.hpp>

namespace web {

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
	typedef std::function<void(request &, response &)> view_function_t;
private:
	std::vector<std::string> args_;

	/**
	 * verb->view map type (a better indexing?)
	 */
	typedef std::map<int /* verb */, view_function_t> verb_map_t;

	/**
	 * path->mapped verbs type
	 */
	typedef std::map<std::string, verb_map_t> view_map_t;

	/**
	 * Map of views.
	 */
	view_map_t views_;

	/**
	 * Server socket file descriptor.
	 */
	int server_socket_;
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
	 * @param verb (GET, POST, ...)
	 * @param path Path.
	 * @param view View function.
	 */
	void mount_route(int verb, std::string const & path, view_function_t view);
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
	 * Convenient shortcut for mounting HEAD view.
	 * @param path Path.
	 * @param view View function.
	 */
	void head(std::string const & path, view_function_t view);
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
	 * Match http_verb and path to a view, then return it.
	 *
	 * @param http_verb HTTP verb (GET, POST, etc.)
	 * @param path View path.
	 */
	view_function_t get_route(int http_verb,
		std::string const & path);
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
	void listen(unsigned short port, const char * address = "127.0.0.1");
};

} /* /namespace web */

#endif /* WEB_APPLICATION_H_INCLUDED_ */

