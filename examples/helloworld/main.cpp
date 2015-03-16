#include <iostream>
#include <web/web.hpp>

struct ExampleController
{
	static void grab_data(web::request & req, web::response & res)
	{
		web::json json = {
			{ "pi", 3.141 },
			{ "happy", true },
			{ "name", "Niels" },
			{ "nothing", nullptr },
			{ "answer", {
				{ "everything", 42 }
			}},
			{ "list", { 1, 0, 2 } },
			{ "object", {
				{ "currency", "USD" },
				{ "value", 42.99 }
			}}
		};

		res.stream() << json;
	}
};

int main(int argc, char * argv[])
{
	web::config::publish("server.port", 4444);

	web::application app(argc, argv);

	try {
		// You can use lambda expressions
		app.get("/", [](web::request & req, web::response & res) {
			res.stream() << "Hello world!";
		});

		// Or simply reference a public static method in a controller
		app.get("/json", ExampleController::grab_data);

		// Render a view easily
		app.get("/view", [](web::request & req, web::response & res) {
			res.stream() << web::view::make("lol", {
				{ "name", "Gloop" },
				{ "age",  4 }
			});
		});

		// Straightforward logging
		app.get("/log", [](web::request & req, web::response & res) {
		    web::log::info("welcome to web");
    		res.stream() << "logged";
		});

		web::log::info("web server started on 127.0.0.1:{}", web::config::get("server.port"));
		app.listen(web::config::get("server.port"));
	} catch (std::exception const & e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
		return 1;
	}
}