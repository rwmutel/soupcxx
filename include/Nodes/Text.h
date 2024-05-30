#ifndef SOUPCXX_TEXT_H
#define SOUPCXX_TEXT_H

#include <vector>
#include <memory>
#include "Node.h"

class Text : public Node {
    std::string text_m;
public:
    Text() = default;
    explicit Text(std::string_view text);
    virtual std::vector<std::shared_ptr<Node>> get_siblings() const override;
    [[nodiscard]] std::string serialize_html() const override;
};


#endif //SOUPCXX_TEXT_H
