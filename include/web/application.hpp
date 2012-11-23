#if !defined(WEB_APPLICATION_H_INCLUDED_)
#define WEB_APPLICATION_H_INCLUDED_

#include <string>
#include <vector>
#include <map>
#include <functional>

#include <web/request.hpp>
#include <web/response.hpp>

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
	 * @param path Path.
	 * @param view View function.
	 */
	void get(std::string const & path, view_function_t view);

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
	 * Process a request and return response.
	 *
	 * @param req A request instance with headers specified.
	 * @param res A response instance
	 */
	void process(request & req, response & res);
};

} /* /namespace web */

#endif /* WEB_APPLICATION_H_INCLUDED_ */

