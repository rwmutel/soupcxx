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
    std::cout << soup.find("a") << std::endl;
    return 0;
}