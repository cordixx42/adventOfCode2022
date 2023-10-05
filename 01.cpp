#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    if (__cplusplus == 201703L)
        std::cout << "C++17\n";
    else if (__cplusplus == 201402L)
        std::cout << "C++14\n";
    else if (__cplusplus == 201103L)
        std::cout << "C++11\n";
    else if (__cplusplus == 199711L)
        std::cout << "C++98\n";
    else
        std::cout << "pre-standard C++\n";
    std::string line;

    std::vector<std::string> a;

    int x;
    std::vector<int> b;
    b.push_back(0);

    int n = 18;

    while (true) {
        std::getline(std::cin, line);
        if (line == "a") {
            break;
        }
        if (line == "") {
            b.push_back(0);

        } else {
            b.insert(b.end() - 1, b.back() + stoi(line));
            b.pop_back();
        }
    }

    std::cout << b.size() << std::endl;
    int max0 = *(std::max_element(b.begin(), b.end()));
    b.erase(std::remove(b.begin(), b.end(), max0), b.end());
    int max1 = *(std::max_element(b.begin(), b.end()));
    b.erase(std::remove(b.begin(), b.end(), max1), b.end());
    int max2 = *(std::max_element(b.begin(), b.end()));

    std::cout << max0 << std::endl;
    std::cout << max1 << std::endl;
    std::cout << max2 << std::endl;
    std::cout << max0 + max1 + max2 << std::endl;

    return 0;
}