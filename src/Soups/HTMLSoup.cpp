#include <string_view>
#include "HTMLSoup.h"
#include "Tag.h"

HTMLSoup::HTMLSoup(std::string_view content) {
    root_m = Tag("html", content.substr(6), nullptr);
}

Tag& HTMLSoup::get_root() {
    return root_m;
}

std::shared_ptr<Node> HTMLSoup::find(std::string_view tag_name) {
    return root_m.find(tag_name);
}

std::vector<std::shared_ptr<Node>> HTMLSoup::find_all(std::string_view tag_name) {
    return root_m.find_all(tag_name);
}

std::string HTMLSoup::serialize() {
    return root_m.serialize_html();
}