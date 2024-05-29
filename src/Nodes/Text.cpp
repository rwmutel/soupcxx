#include "Text.h"

Text::Text(std::string_view text) :
    text_m(text) {
    tag_name_m = "text";
}

std::string Text::serialize_html() const {
    return text_m;
}
