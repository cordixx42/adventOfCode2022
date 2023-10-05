#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    system("stty raw");

    char c;

    std::vector<char> fourteen;

    std::vector<char> operation;

    int index = 14;

    for (int i = 0; i < index; i++) {
        fourteen.push_back(getchar());
    }

    while (true) {
        index++;
        fourteen.push_back(getchar());
        fourteen.erase(fourteen.begin());
        std::vector<char> operation(fourteen);
        sort(operation.begin(), operation.end());
        // unique(operation.begin(), operation.end());
        // std::cout << fourteen.size() << std::endl;
        // std::cout << operation.size() << std::endl;
        if (std::adjacent_find(operation.begin(), operation.end()) == operation.end()) {
            break;
        }
    }

    system("stty cooked");

    std::cout << index << std::endl;
}