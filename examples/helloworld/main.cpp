#include <gud/gud.hpp>

struct ExampleController
{
	static std::string grab_data(gud::request & req, gud::response & res)
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

		return json;
	}
};

int main(int argc, char * argv[])
{
	// We can modify or set any settings at any time easily
	gud::config::publish("server.port", 4444);

	// Change this to the path of your gud build
	gud::config::publish("app.paths.root", "/home/pizzapi/code/gud/build/examples/helloworld");
	gud::config::publish("app.paths.views", "/views");

	// Initialize our application server
	gud::application app(argc, argv);

	// Uncomment this and try it after creating and populating database
	/*
		auto res = gud::db::query("SELECT * FROM tbl");
		res.each([](gud::db::results row) {
			std::string test = row["name"];
			std::cout << test << std::endl;
		});
	*/

	try {
		// You can use lambda expressions
		app.get("/", [](gud::request & req, gud::response & res) {
			return "Hello world!";
		});

		// Get input data from post request and print it out
		app.post("/post", [](gud::request & req, gud::response & res) {
			return "headers:\n\n" + req.raw_headers()
				 + "body:\n\n"    + req.raw_body();
		});

		// Or simply reference a public static method in a controller
		app.get("/json", ExampleController::grab_data);

		// Render a view easily
		app.get("/view", [](gud::request & req, gud::response & res) {
			return gud::view::make("home.mustache", {
				{ "name", "Gloop" },
				{ "age",  std::to_string(4) }
			});
		});

		// Straightforward logging
		app.get("/log", [](gud::request & req, gud::response & res) {
		    gud::log::info("welcome to gud");
    		return "logged";
		});

		app.listen(gud::config::get("server.port"));
	} catch (std::exception const & e) {
		gud::log::error("Caught exception: {}", e.what());
		return 1;
	}
}