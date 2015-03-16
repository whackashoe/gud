#if !defined(WEB_VIEW_H_INCLUDED_)
#define WEB_VIEW_H_INCLUDED_

#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <web/json.hpp>
#include <web/config.hpp>
#include <web/plustache/plustache_types.hpp>
#include <web/plustache/template.hpp>

namespace web {

/**
 * Render templates
 */
class view
{
private:
    /**
     * From config grab the directory views reside in
     */
    static std::string get_view_dir();
public:
    /**
     * Render a view without passing any data
     */
    static std::string make(const std::string & path);

    /**
     * Render a view that contains input data
     */
    static std::string make(const std::string & path, web::json data);
};

} /* /namespace web */

#endif /* WEB_VIEW_H_INCLUDED_ */