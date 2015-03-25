#if !defined(GUD_UTIL_H_INCLUDED_)
#define GUD_UTIL_H_INCLUDED_

#include <string>
#include <ctime>

namespace gud {

/**
 * Utility functions.
 */
class util
{
public:
    static std::string rfc1123_datetime(time_t time);
};

} /* /namespace gud */

#endif /* GUD_UTIL_H_INCLUDED_ */