#include <iostream>
#include "ranges_2.hpp"
#include <vector>


int main() {
    
    for (auto i : range(10, 0, -1)) {
        std::cout << i << "\n";
    }
    
    short N = 10;
    for (char rx : range(97,97+N)) {
        std::cout << rx << ", ";
    }
    
    std::cout << "Iterating over pointers:\n";
    auto v = std::vector<int>{1,2,3,4,5,6};
    // a simple and not really realistic example
    for (auto it : range(v.begin(), v.end())) {
        std::cout << *it << ", ";
    }
    std::cout << "\n";
    
    for (auto fi : range(1.0, 3.3, 0.1))
    {
        std::cout << fi << ", ";
    }
}
