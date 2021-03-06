# gud

Standard web framework for C++11.

## Introduction

Let's write sexy web apps in pure C++!

This is a continuance and going in a different direction from the good work of [Michał Papierski](https://github.com/mpapierski/web).

## Features

* Kickass router
* get, put, patch, post, etc
* High test coverage.
* Json reading and writing utility
* Logging ability
* Templating provided via mustache (unfinished)
* Easy to use config system
* Mysql database handler

## Requirements

* CMake (2.6+)
* C++11 compliant compiler.
* Boost Regex

## Example

```cpp
int main(int argc, char * argv[])
{
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
```

## Installation

```sh
sudo apt-get update
sudo apt-get install libboost-dev libboost-regex-dev cmake libmysqlclient-dev libmysqlcppconn-dev
git clone https://github.com/whackashoe/gud.git
cd gud/build
cmake ..
make
./examples/helloworld/helloworld
```