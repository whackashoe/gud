#include <web/view.hpp>

using namespace web;

std::string view::make(const std::string & path)
{
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return str;
}

std::string view::make(const std::string & path, web::json input)
{
    std::ifstream t(path);
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