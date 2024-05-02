#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H
#include <variant>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std::literals;

using Attribute = std::variant<std::string, std::vector<std::string>>;

enum class AttributeType {
    ID,
    CLASS,
    ATTRIBUTE,
    TAG_NAME
};

enum class SoupType {
    HTML,
    MD
};

enum class TagType {
    HTML,
    HEAD,
    TITLE,
    BODY,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    P,
    DIV,
    SPAN,
    A,
    IMG,
    UL,
    OL,
    LI
};

#endif //PROJECT_UTILS_H
