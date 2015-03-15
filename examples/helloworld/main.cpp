#include <iostream>
#include <web/web.hpp>


int main(int argc, char * argv[])
{
	web::application app(argc, argv);
	constexpr int port = 3333;

	try {
		app.get("/", [](web::request & req, web::response & res) {
			res.stream() << "Hello world!";
		});

		app.get("/json", [](web::request & req, web::response & res) {
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
		});

		std::cout << "web server started on 127.0.0.1:" << port << std::endl;
		app.listen(port);
	} catch (std::exception const & e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
		return 1;
	}
}