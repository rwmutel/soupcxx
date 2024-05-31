#include "soupcxx.h"
#include <iostream>
#include <fstream>

using namespace std::literals;

int main() {
    std::ifstream alice{"../data/alice_large.html"};
    std::string content{std::istreambuf_iterator<char>(alice), std::istreambuf_iterator<char>()};

    HTMLSoup soup{content};
    (*dynamic_cast<Tag*>(soup.find("a").get()))["class"] = "test_class";
    soup.serialize_to_file("../data/alice_out.html");

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

    std::cout << "Find the names of children of the html tag and compare them with descendants" << std::endl;
    auto children = soup.get_root().get_children();
    auto descendants = soup.get_root().get_descendants();
    std::cout << "Children tags (only the direct children nodes)" << std::endl;
    for (const auto& child : children) {
        std::cout << child->get_tag_name() << std::endl;
    }
    std::cout << "Descendants tags (all the nodes lower in the hierarchy)" << std::endl;
    for (const auto& descendant : descendants) {
        std::cout << descendant->get_tag_name() << std::endl;
    }
    return 0;
}