#include <gud/util.hpp>

using namespace gud;

std::string util::rfc1123_datetime(time_t time)
{
    struct tm * timeinfo;
    char buffer [80];

    timeinfo = gmtime ( &time );
    strftime (buffer,80,"%a, %d %b %Y %H:%M:%S GMT",timeinfo);

    return buffer;
}