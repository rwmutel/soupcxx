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
    std::vector<std::shared_ptr<Node>> find_all(std::string_view tag_name);
    std::string serialize() override;
    void serialize_to_file(const std::filesystem::path& path);
};


#endif //PROJECT_HTMLSOUP_H
