 #if !defined(GUD_CONFIG_H_INCLUDED_)
#define GUD_CONFIG_H_INCLUDED_

#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <gud/json.hpp>
#include <gud/util.hpp>

namespace gud {

/**
 * gud settings
 */
class config
{
private:
    static gud::json settings_;

public:

    /**
     * Get configuration setting
     * Config is stored in a nested obj
     * You can access deeper levels of config with dot notation
     * ie: "translations.english.introduction"
     */
    static gud::json get(std::string const & field);

    /**
     * Push settings into field
     * you can use dot notation like above
     */
    static void publish(std::string const & field, gud::json conf);
};

} /* /namespace gud */

#endif /* GUD_CONFIG_H_INCLUDED_ */
