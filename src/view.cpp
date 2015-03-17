#include <gud/view.hpp>

using namespace gud;

std::string view::get_view_dir()
{
    std::string root = config::get("app.paths.root");
    std::string vsrc = config::get("app.paths.views");

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
    std::ifstream t(view::get_view_dir() + path);
    std::string content((std::istreambuf_iterator<char>(t)),
                         std::istreambuf_iterator<char>());

    // TODO
    // once json supports grabbing keys
    // lets populate pstache data and render

    PlustacheTypes::ObjectType data;
    for(auto i : input) {
        std::cout << i << std::endl;
    }

    data["name"] = "Gloop";
    data["age"] = "5";

    Plustache::template_t tpl;

    return tpl.render(content, data);
}