#include <string_view>
#include "HTMLSoup.h"
#include "Tag.h"

HTMLSoup::HTMLSoup(std::string_view content) {
    root_m = Tag("html", content.substr(6, content.size() - 7));
}

Tag& HTMLSoup::get_root() {
    return root_m;
}
