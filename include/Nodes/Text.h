#ifndef SOUPCXX_TEXT_H
#define SOUPCXX_TEXT_H

#include "Node.h"

class Text : public Node {
    std::string text_m;
public:
    Text() = default;
    explicit Text(std::string_view text);
    [[nodiscard]] std::string serialize_html() const override;
};


#endif //SOUPCXX_TEXT_H
