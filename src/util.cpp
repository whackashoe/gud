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

std::vector<std::string> util::undot(std::string const & field)
{
    std::vector<std::string> tokens;
    boost::split(tokens, field, boost::is_any_of("."), boost::token_compress_on);
    return tokens;
}
