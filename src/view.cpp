#include <gud/view.hpp>

using namespace gud;

std::string view::get_view_dir()
{
    std::string const & root = config::get("app.paths.root");
    std::string const & vsrc = config::get("app.paths.views");

    return root + vsrc;
}

std::string view::make(const std::string & path)
{
    std::ifstream t(view::get_view_dir() + path);

    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return str;
}

std::string view::make(const std::string & path, gud::json input)
{
    std::ifstream t(view::get_view_dir() + "/" + path);
    std::string const content((std::istreambuf_iterator<char>(t)),
                               std::istreambuf_iterator<char>());

    PlustacheTypes::ObjectType data;
    for(auto it = input.begin(); it != input.end(); ++it) {
        std::string const & key = it.key();
        std::string const & val = it.value();
        data[key] = val;
    }

    Plustache::template_t tpl;

    return tpl.render(content, data);
}