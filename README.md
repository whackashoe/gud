# web [![Build Status](https://secure.travis-ci.org/whackashoe/web.png)](http://travis-ci.org/whackashoe/web)

Standard web framework for C++11.

## Introduction

Let's write sexy web apps in pure C++!

## Features

* Kickass router
* get, put, patch, post, etc
* High test coverage.
* Json reading and writing utility
* Logging ability
* Templating provided via mustache

## Requirements

* CMake (2.6+)
* C++11 compliant compiler.
* Boost Regex

## Example

```cpp
int main(int argc, char * argv[])
{
	web::application app(argc, argv);
	constexpr int port = 3333;

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

		web::log::info("web server started on 127.0.0.1:{}", port);
		app.listen(port);
	} catch (std::exception const & e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
		return 1;
	}
}
```

Now just compile this code and point your web browser at http://localhost:3333/.

