#include "soupcxx.h"
#include <iostream>
#include <fstream>

using namespace std::literals;

int main() {
    std::ifstream alice{"../data/alice.html"};
    std::string content{std::istreambuf_iterator<char>(alice), std::istreambuf_iterator<char>()};

    HTMLSoup soup{content};
    std::ofstream alice_out{"../data/alice_out.html"};
    alice_out << soup.get_root().serialize_html() << std::endl;
    std::cout << "Find the first link tag: " << std::endl;
    auto a = soup.find("a");
    std::cout << a->serialize_html() << std::endl;

    std::cout << "Find all links in <a> tags: " << std::endl;
    for (const auto& tag : soup.find_all("a")) {
        std::cout << std::get<std::string>((*dynamic_cast<Tag*>(tag.get()))["href"]) << std::endl;
    }
    std::cout << "Find the parent of the first link tag: " << std::endl;
    std::cout << "tag name: " << a->get_parent()->get_tag_name() << ", class: "
        << std::get<std::string>((*dynamic_cast<Tag*>(a->get_parent()))["class"]) << std::endl;
    return 0;
}