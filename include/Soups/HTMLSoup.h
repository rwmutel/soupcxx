#ifndef PROJECT_HTMLSOUP_H
#define PROJECT_HTMLSOUP_H
#include "Soup.h"
#include "Tag.h"

class HTMLSoup : public Soup {
    Tag root_m;
public:
    explicit HTMLSoup(std::string_view content);
    Tag& get_root();
    std::shared_ptr<Node> find(std::string_view tag_name);
//    Node& find(std::regex pattern, AttributeType type=AttributeType::TAG_NAME) override;
//    Node& find(std::function <bool(Node)> predicate) override;
    std::vector<std::shared_ptr<Node>> find_all(std::string_view tag_name);
//    std::vector<Node> find_all(std::regex pattern, AttributeType type=AttributeType::TAG_NAME) override;
    std::string serialize() override;
//    void serialize_to_file(std::filesystem::path path) override;
};


#endif //PROJECT_HTMLSOUP_H
