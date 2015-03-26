#define BOOST_TEST_MODULE application
#include <boost/test/included/unit_test.hpp>

#include <gud/gud.hpp>

using namespace boost;

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_application_constructor)
{
	gud::application app1(0, 0);
	BOOST_REQUIRE_EQUAL(app1.args().size(), 0);
	const char * args[] = {"./test"};
	gud::application app2(1, const_cast<char**>(args));
	BOOST_REQUIRE_EQUAL(app2.args().size(), 1);
	BOOST_REQUIRE_EQUAL(app2.args()[0], "./test");
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_application_router)
{
	const char * args[] = {"./test"};
	gud::application app(1, const_cast<char**>(args));
	BOOST_REQUIRE_EQUAL(app.routes().size(), 0);
	app.get("/", [](gud::request&, gud::response& res) {
		return "Hello world!";
	});
	BOOST_REQUIRE_EQUAL(app.routes().size(), 1);
	BOOST_REQUIRE_EQUAL(app.routes().find("/")->second.size(), 1);
	// Mount again, check if data did not changed.
	BOOST_CHECK_THROW(app.get("/", [](gud::request&, gud::response&){ return ""; }), std::logic_error);
	BOOST_REQUIRE_EQUAL(app.routes().size(), 1);
	BOOST_REQUIRE_EQUAL(app.routes().find("/")->second.size(), 1);
	// Process route / with GET verb.
	gud::application::view_function_t view = app.get_route(gud::request::http_method::GET, "/");
	BOOST_REQUIRE(view);
	// Same path, different verb.
	BOOST_CHECK(!app.get_route(gud::request::http_method::POST, "/"));
	// Path not found.
	BOOST_CHECK(!app.get_route(gud::request::http_method::GET, "/path2"));

	// Run the view with fake req/res pair.
	gud::request req("GET / HTTP/1.1\r\n\r\n");
	gud::response res;
	std::string data = app.process(req, res);
	BOOST_REQUIRE_EQUAL(res.raw_body(), "Hello world!");
	// Raw response:
	const char * raw_response = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nContent-Length: 12\r\n\r\nHello world!";
	BOOST_REQUIRE_EQUAL(data, raw_response);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_application_router_wildcard)
{
	const char * args[] = {"./test"};
	gud::application app(1, const_cast<char**>(args));
	BOOST_REQUIRE_EQUAL(app.routes().size(), 0);
	// Set wildcard view.
	app.all("/", [](gud::request& req, gud::response& res) {
		return "Method is... " + req.method_s();
	});

	// Check if get_route returns valid functor.
	gud::application::view_function_t wildcard1 = app.get_route(gud::request::http_method::GET, "/");
	gud::application::view_function_t wildcard2 = app.get_route(gud::request::http_method::POST, "/");
	BOOST_REQUIRE(wildcard1);
	BOOST_REQUIRE(wildcard2);
	//
	BOOST_REQUIRE_EQUAL(app.routes().find("/")->second.size(), 1);

	// Navigate to "/" using various methods.

	gud::request req_get("GET / HTTP/1.1\r\n\r\n");
	gud::response res_get;
	std::string data = app.process(req_get, res_get);
	BOOST_REQUIRE_EQUAL(res_get.raw_body(), "Method is... GET");
	const char * raw_response_get = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nContent-Length: 16\r\n\r\nMethod is... GET";
	BOOST_REQUIRE_EQUAL(data, raw_response_get);

	gud::request req_post("POST / HTTP/1.1\r\n\r\n");
	gud::response res_post;
	data = app.process(req_post, res_post);
	BOOST_REQUIRE_EQUAL(res_post.raw_body(), "Method is... POST");
	const char * raw_response_post = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nContent-Length: 17\r\n\r\nMethod is... POST";
	BOOST_REQUIRE_EQUAL(data, raw_response_post);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_application_router_return_http_error)
{
	const char * args[] = {"./test"};
	gud::application app(1, const_cast<char**>(args));
	BOOST_REQUIRE_EQUAL(app.routes().size(), 0);
	app.all("/wildcard/", [](gud::request& req, gud::response& res) {
		if (req.method_s() == "GET")
		{
			return "You're welcome!";
		}
		res.set_status_code(403);
		return "You're not welcome!";
	});
	app.get("/error1/", [](gud::request&, gud::response& res) {
		// Buffered data is ignored.
		return "Hello world!";
		// Results in "500" response - server error
		// with a message obtained from .what().

		throw std::runtime_error("wat");
	});
	BOOST_REQUIRE(app.get_route(gud::request::http_method::GET, "/wildcard/"));
	BOOST_REQUIRE(app.get_route(gud::request::http_method::POST, "/wildcard/"));
	// Prepare request
	gud::request req_get("GET /wildcard/ HTTP/1.1\r\n\r\n");
	gud::response res_get;

	std::string data = app.process(req_get, res_get);
	BOOST_REQUIRE_EQUAL(res_get.raw_body(), "You're welcome!");
	BOOST_REQUIRE_EQUAL(data, "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nContent-Length: 15\r\n\r\nYou're welcome!");

	gud::request req_post("POST /wildcard/ HTTP/1.1\r\n\r\n");
	gud::response res_post;

	std::string().swap(data);
	data = app.process(req_post, res_post);
	BOOST_REQUIRE_EQUAL(res_post.raw_body(), "You're not welcome!");
	BOOST_REQUIRE_EQUAL(data, "HTTP/1.1 403 OK\r\nContent-Type:text/html\r\nContent-Length: 19\r\n\r\nYou're not welcome!");

	// Return 404
	gud::request req_404("GET /doesnotexists/ HTTP/1.1\r\n\r\n");
	gud::response res_404;

	data = app.process(req_404, res_404);
	BOOST_REQUIRE_EQUAL(res_404.raw_body(), "");
	BOOST_REQUIRE_EQUAL(data, "HTTP/1.1 404 OK\r\nContent-Type:text/html\r\nContent-Length: 0\r\n\r\n");

	// 500 - unknown exception (std::exception based)
	gud::request req_500a("GET /error1/ HTTP/1.1\r\n\r\n");
	gud::response res_500a;

	data = app.process(req_500a, res_500a);
	BOOST_REQUIRE_EQUAL(res_500a.raw_body(), "Hello world!");
	BOOST_REQUIRE_EQUAL(data, "HTTP/1.1 500 OK\r\nContent-Type:text/html\r\nContent-Length: 3\r\n\r\nwat");

}

//____________________________________________________________________________//
