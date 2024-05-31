#include "soupcxx.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <atomic>

using namespace std::literals;

inline std::chrono::steady_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::steady_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


int main() {
    std::ifstream alice{"../data/alice_large.html"};
    std::string content{std::istreambuf_iterator<char>(alice), std::istreambuf_iterator<char>()};

    size_t total_time = 0;
    for (size_t i = 0; i < 30; ++i) {
        std::ofstream dump{"../data/alice_links_soupcxx.html"};
        auto start = get_current_time_fenced();
        HTMLSoup soup{content};
        auto link_nodes = soup.find_all("a");
        std::vector<std::string> links;
        for (const auto& node : link_nodes) {
            links.push_back(std::get<std::string>((*dynamic_cast<Tag*>(node.get()))["href"]));
        }
        auto end = get_current_time_fenced();
        for (const auto& link : links) {
            dump << link << std::endl;
        }
        total_time += to_us(end - start);
    }
    std::cout << total_time << std::endl;

    return 0;
}