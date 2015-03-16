#if !defined(WEB_VIEW_H_INCLUDED_)
#define WEB_VIEW_H_INCLUDED_

#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <web/json.hpp>
#include <web/plustache/plustache_types.hpp>
#include <web/plustache/template.hpp>

namespace web {

/**
 * HTTP response.
 */
class view
{
private:

public:
    static std::string make(const std::string & path);
    static std::string make(const std::string & path, web::json data);
};

} /* /namespace web */

#endif /* WEB_VIEW_H_INCLUDED_ */