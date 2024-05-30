#ifndef PROJECT_TAG_H
#define PROJECT_TAG_H
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <regex>
#include <optional>
#include <memory>
#include "Node.h"
#include "utils.h"

class Tag : public Node {
    std::vector<std::shared_ptr<Node>> children_m;
    std::unordered_map<std::string, Attribute> attributes_m;
public:
    Tag() = default;
    Tag(std::string&& tag_name, std::string_view text, Tag* parent);

//    virtual std::vector<Node> get_children();
//
//    virtual std::vector<Node> get_descendants();
//    virtual Node& find(std::regex pattern, AttributeType type=AttributeType::TAG_NAME);
//
    virtual std::shared_ptr<Node> find(std::string_view tag_name);
//    virtual Node& find(std::function <bool(Node)> predicate);
//    virtual std::vector<Node> find_all(std::regex pattern, AttributeType type=AttributeType::TAG_NAME);
    virtual std::vector<std::shared_ptr<Node>> find_all(std::string_view tag_name);

    virtual Attribute operator[](const std::string& key) const;
    std::string serialize_html() const override;
    virtual ~Tag() override;
};


#endif //PROJECT_TAG_H
