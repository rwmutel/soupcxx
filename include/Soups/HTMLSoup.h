#ifndef PROJECT_HTMLSOUP_H
#define PROJECT_HTMLSOUP_H
#include "Soup.h"
#include "Tag.h"

class HTMLSoup : public Soup {
    Tag root_m;
public:
    explicit HTMLSoup(std::string_view content);
    Tag& get_root();
//    Node& find(std::regex pattern, AttributeType type=AttributeType::TAG_NAME) override;
//    Node& find(TagType tag_name) override;
//    Node& find(std::function <bool(Node)> predicate) override;
//    std::vector<Node> find_all(std::regex pattern, AttributeType type=AttributeType::TAG_NAME) override;
//    std::vector<Node> find_all(TagType tag_name) override;
//    Soup prettify() override;
//    void prettify_in_place() override;
//    std::string serialize() override;
//    void serialize_to_file(std::filesystem::path path) override;
};


#endif //PROJECT_HTMLSOUP_H
