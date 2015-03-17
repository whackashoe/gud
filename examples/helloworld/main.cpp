#include <iostream>
#include <gud/gud.hpp>

struct ExampleController
{
	static void grab_data(gud::request & req, gud::response & res)
	{
		gud::json json = {
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
	gud::config::publish("server.port", 4444);

	gud::application app(argc, argv);

	try {
		// You can use lambda expressions
		app.get("/", [](gud::request & req, gud::response & res) {
			res.stream() << "Hello world!";
		});

		// Or simply reference a public static method in a controller
		app.get("/json", ExampleController::grab_data);

		// Render a view easily
		app.get("/view", [](gud::request & req, gud::response & res) {
			res.stream() << gud::view::make("lol", {
				{ "name", "Gloop" },
				{ "age",  4 }
			});
		});

		// Straightforward logging
		app.get("/log", [](gud::request & req, gud::response & res) {
		    gud::log::info("welcome to gud");
    		res.stream() << "logged";
		});

		gud::log::info("gud server started on 127.0.0.1:{}", gud::config::get("server.port"));
		app.listen(gud::config::get("server.port"));
	} catch (std::exception const & e) {
		gud::log::error("Caught exception: {}", e.what());
		return 1;
	}
}