#include <string_view>
#include "HTMLSoup.h"
#include "Tag.h"

HTMLSoup::HTMLSoup(std::string_view content) {
    root_m = Tag("html", content.substr(6, content.size() - 7));
}

Tag& HTMLSoup::get_root() {
    return root_m;
}

std::optional<Tag> HTMLSoup::find(std::string_view tag_name) {
    return root_m.find(tag_name);
}

std::vector<Tag> HTMLSoup::find_all(std::string_view tag_name) {
    return root_m.find_all(tag_name);
}

//std::vector<Node> HTMLSoup::find_all(TagType tag_name) {
//    return std::vector<Node>();
//}
