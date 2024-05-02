#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H
#include <string>

class Node {
public:
    Node() = default;
    Node& operator=(const Node&) = default;

//    virtual Node& get_parent()=0;
    virtual std::string serialize_html() const =0;
//    std::string serialize_md();
    virtual ~Node() = default;
};


#endif //PROJECT_NODE_H
