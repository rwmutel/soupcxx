#include "Tag.h"
#include "Text.h"
#include <optional>

std::vector<std::shared_ptr<Node>> parse_top_level_html(
        std::string_view content,
        Tag* parent) {
    std::size_t tag_end_pos;
    std::size_t name_end_pos;
    std::size_t first_space_pos;
    std::size_t first_bracket_pos;
    std::size_t first_backward_bracket_pos = content.find('>');
    std::string_view tag_name;
    std::size_t tag_name_size;
    std::vector<std::shared_ptr<Node>> tags;
    std::size_t start_pos = 0;
    while (std::isspace(content[start_pos])) {
        ++start_pos;
    }
    if (content[start_pos] != '<' && first_backward_bracket_pos != std::string::npos) {
        start_pos = first_backward_bracket_pos + 1;
    }
    for(std::size_t i = start_pos; i < content.size(); i++) {
        if (std::isspace(content[i])) {
            continue;
        }
        else if (content[i] == '<' && content[i + 1] != '/') {
            first_space_pos = content.find(' ', i);
            first_bracket_pos = content.find('>', i);
            name_end_pos = std::min(first_space_pos, first_bracket_pos);
            tag_name = content.substr(i + 1, name_end_pos - i - 1);
            tag_name_size = name_end_pos - i - 1;
            tag_end_pos = content.find("</"s + std::string(tag_name) + ">"s, i);
            tags.emplace_back(std::make_shared<Tag>(
                    std::string(tag_name),
                    content.substr(name_end_pos + 1, tag_end_pos - i - 2 - tag_name_size),
                    parent
                    ));
            i = tag_end_pos + 1;
        }
        else {
            first_bracket_pos = content.find('<', i);
            first_backward_bracket_pos = content.find('>', i);
            if (first_bracket_pos == std::string::npos && first_backward_bracket_pos == std::string::npos) {
                tags.emplace_back(std::make_shared<Text>(content.substr(i)));
                break;
            }
            if (first_bracket_pos < first_backward_bracket_pos && first_bracket_pos != i) {
                tags.emplace_back(std::make_shared<Text>(content.substr(i, first_bracket_pos - i)));
                i = first_bracket_pos - 1;
            }
        }
    }
    return tags;
}

std::vector<std::string> parse_multivariate_attr(std::string_view content) {
    std::vector<std::string> attr_vals;
    std::size_t space_pos = content.find(' ');
    while (space_pos != std::string::npos) {
        attr_vals.emplace_back(content.substr(0, space_pos));
        content = content.substr(space_pos + 1);
        space_pos = content.find(' ');
    }
    return attr_vals;
}

void filter_attr_val_inplace(std::string& attr_val) {
    for (std::size_t i = 0; i < attr_val.size(); i++) {
        if (attr_val[i] == '\"' || attr_val[i] == '\'' || attr_val[i] == ' ') {
            attr_val.erase(i, 1);
        }
    }
}

std::unordered_map<std::string, Attribute> parse_html_attributes(std::string_view content) {
    std::unordered_map<std::string, Attribute> parsed_attributes;
    std::string_view opening_tag = content.substr(0, content.find('>'));
    std::size_t eq_pos = opening_tag.find('=');
    std::size_t attr_name_start_pos;
    std::size_t attr_end_pos;
    std::string attr_name;
    std::string attr_val;
    while (eq_pos != std::string::npos) {
        attr_name_start_pos = opening_tag.find_last_of(' ', eq_pos) + 1;
        attr_name = std::string(opening_tag.substr(attr_name_start_pos,  eq_pos - attr_name_start_pos));
        attr_end_pos = opening_tag.find_first_of(" >\"", eq_pos + 2) - 1;
        attr_val = std::string(opening_tag.substr(eq_pos + 1, attr_end_pos - eq_pos));
        filter_attr_val_inplace(attr_val);
        if (attr_val.find(' ') != std::string::npos) {
            parsed_attributes[attr_name] = parse_multivariate_attr(attr_val);
        } else {
            parsed_attributes[attr_name] = attr_val;
        }
        eq_pos = opening_tag.find('=', attr_end_pos + 1);
    }

    return parsed_attributes;
}

Tag::Tag(std::string&& tag_name, std::string_view text, Tag* parent) :
    children_m(parse_top_level_html(text, this)),
    attributes_m(parse_html_attributes(text)) {
    tag_name_m = tag_name;
    parent_m = parent;
}

std::string Tag::serialize_html() const {
    std::string serialized_html = '<' + tag_name_m + (attributes_m.empty() ? "" : " ");
    for (const auto& [attr_name, attr_val] : attributes_m) {
        std::string attr_serialized = attr_name + "=\"";
        if (std::holds_alternative<std::string>(attr_val)) {
            attr_serialized += std::get<std::string>(attr_val) + '\"';
        } else {
            for (const auto& val : std::get<std::vector<std::string>>(attr_val)) {
                attr_serialized += val;
                attr_serialized += val == std::get<std::vector<std::string>>(attr_val).back() ? '\"' : ' ';
            }
        }
        serialized_html += attr_serialized + ' ';
    }
    serialized_html += ">\n";
    const std::string indent{"  "};
    for (const auto& child: children_m) {
        auto serialized_child = child->serialize_html();
        size_t startPos = 0;
        while (startPos < serialized_child.size()) {
            size_t endPos = serialized_child.find('\n', startPos);
            if (endPos == std::string::npos) {
                endPos = serialized_child.size();
            }
            serialized_html += indent + serialized_child.substr(startPos, endPos - startPos) + "\n";
            startPos = endPos + 1;
        }
    }
    if (serialized_html.back() != '\n')
        serialized_html += '\n';
    serialized_html += "</" + tag_name_m + ">\n";
    return serialized_html;
}

std::shared_ptr<Node> Tag::find(std::string_view tag_name) {
    std::shared_ptr<Node> child_found;
    for (auto& child : children_m) {
        auto child_tag_name = child->get_tag_name();
        if (child_tag_name == tag_name) {
            return child;
        }
        if (child_tag_name != "text") {
            child_found = dynamic_cast<Tag*>(child.get())->find(tag_name);
            if (child_found) {
                return child_found;
            }
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Node>> Tag::find_all(std::string_view tag_name) {
    std::vector<std::shared_ptr<Node>> found_tags;
    for (auto& child : children_m) {
        if (child->get_tag_name() == tag_name) {
            found_tags.push_back(child);
        }
        if (child->get_tag_name() != "text") {
            auto child_nodes = dynamic_cast<Tag*>(child.get())->find_all(tag_name);
            for (auto &found_child: child_nodes) {
                found_tags.push_back(found_child);
            }
        }
    }
    return found_tags;
}

Attribute Tag::operator[](const std::string& key) const {
    return attributes_m.at(key);
}

Tag::~Tag() {
    children_m.clear();
    attributes_m.clear();
}
