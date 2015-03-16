 #if !defined(WEB_CONFIG_H_INCLUDED_)
#define WEB_CONFIG_H_INCLUDED_

#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <web/json.hpp>

namespace web {

/**
 * web settings
 */
class config
{
private:
    static web::json settings_;

public:

    /**
     * Get configuration setting
     * Config is stored in a nested obj
     * You can access deeper levels of config with dot notation
     * ie: "translations.english.introduction"
     */
    static web::json get(std::string const & field);

    /**
     * Push settings into field
     * you can use dot notation like above
     */
    static void publish(std::string const & field, web::json conf);
};

} /* /namespace web */

#endif /* WEB_CONFIG_H_INCLUDED_ */
