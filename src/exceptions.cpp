#include <gud/exceptions.hpp>

using namespace gud;

http_error::http_error(unsigned int error_code) throw()
	: error_code_(error_code)
{
	//
}

const char * http_error::what() const throw()
{
	return "";
}

unsigned int http_error::error_code() const throw()
{
	return error_code_;
}