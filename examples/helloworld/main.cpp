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

		std::cout << "web server started on 127.0.0.1:" << port << std::endl;
		app.listen(port);
	} catch (std::exception const & e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
		return 1;
	}
}