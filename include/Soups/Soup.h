#ifndef PROJECT_SOUP_H
#define PROJECT_SOUP_H
#include <memory>
#include <string_view>
#include <filesystem>
#include <vector>
#include <regex>
#include "Node.h"
#include "utils.h"
#include "Tag.h"

class Soup {
public:
//    virtual Node& find(std::regex pattern, AttributeType type=AttributeType::TAG_NAME)=0;
    virtual std::shared_ptr<Node> find(std::string_view tag_name)=0;
//    virtual Node& find(std::function <bool(Node)> predicate)=0;
//    virtual std::vector<Node> find_all(std::regex pattern, AttributeType type=AttributeType::TAG_NAME)=0;
    virtual std::vector<std::shared_ptr<Node>> find_all(std::string_view tag_name)=0;
//    virtual Soup prettify()=0;
//    virtual void prettify_in_place()=0;
//    virtual std::string serialize()=0;
//    virtual void serialize_to_file(std::filesystem::path path)=0;
};

#endif //PROJECT_SOUP_H
