#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H
#include <string>
#include <memory>

class Node {
protected:
    std::string tag_name_m;
    Node* parent_m;
public:
    Node() = default;
    Node& operator=(const Node&) = default;

    [[nodiscard]] virtual Node* get_parent() const {return parent_m;};
    [[nodiscard]] virtual std::string get_tag_name() const {return tag_name_m;};
    [[nodiscard]] virtual std::string serialize_html() const = 0;
    virtual ~Node() = default;
};


#endif //PROJECT_NODE_H
