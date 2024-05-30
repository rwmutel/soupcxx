#include "soupcxx.h"
#include <iostream>
#include <fstream>

using namespace std::literals;

int main() {
    std::ifstream alice{"../data/alice.html"};
    std::string content{std::istreambuf_iterator<char>(alice), std::istreambuf_iterator<char>()};

    HTMLSoup soup{content};
    std::ofstream alice_out{"../data/alice_out.html"};
    (*dynamic_cast<Tag*>(soup.find("a").get()))["class"] = "test_class";
    alice_out << soup.serialize() << std::endl;

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

    std::cout << "Find the siblings of the first link tag: " << std::endl;
    for (const auto& sibling : a->get_siblings()) {
        std::cout << "tag name: " << sibling->get_tag_name()
            << "\n<serialized>\n" << sibling->serialize_html() << "</serialized>\n" << std::endl;
    }
    return 0;
}