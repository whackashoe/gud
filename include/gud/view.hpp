#if !defined(GUD_VIEW_H_INCLUDED_)
#define GUD_VIEW_H_INCLUDED_

#include <string>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <gud/json.hpp>
#include <gud/config.hpp>
#include <gud/plustache/plustache_types.hpp>
#include <gud/plustache/template.hpp>

namespace gud {

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
    static std::string make(const std::string & path, gud::json data);
};

} /* /namespace gud */

#endif /* GUD_VIEW_H_INCLUDED_ */