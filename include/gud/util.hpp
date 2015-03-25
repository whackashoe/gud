#if !defined(GUD_UTIL_H_INCLUDED_)
#define GUD_UTIL_H_INCLUDED_

#include <string>
#include <ctime>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace gud {

/**
 * Utility functions.
 */
class util
{
public:
    static std::string rfc1123_datetime(time_t time);
    static std::vector<std::string> undot(std::string const & field);
};

} /* /namespace gud */

#endif /* GUD_UTIL_H_INCLUDED_ */