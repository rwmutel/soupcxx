#include "Text.h"
#include "Tag.h"
#include "utils.h"

Text::Text(std::string_view text) :
    text_m(text) {
    tag_name_m = TEXT_NODE;
}

std::string Text::serialize_html() const {
    return text_m;
}

std::vector<std::shared_ptr<Node>> Text::get_siblings() const {
    return dynamic_cast<Tag*>(parent_m)->get_children();
}
