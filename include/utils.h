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

#endif //PROJECT_UTILS_H
