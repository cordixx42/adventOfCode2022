#include <iostream>
#include <vector>

int prio(char c) {
    // a - - z
    if (c >= 97) {
        return c - 96;
    } else {
        return c - 38;
    }
}

int main() {
    std::string line;

    int sum = 0;
    char both = 'a';

    while (true) {
        std::getline(std::cin, line);

        if (line == "a") {
            break;
        }

        int n = line.length() / 2;

        char cp1[n + 1];
        char cp2[n + 1];

        strcpy(cp1, line.substr(0, n).c_str());

        strcpy(cp2, line.substr(n, n).c_str());

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cp1[i] == cp2[j]) {
                    both = cp1[i];
                    break;
                }
            }
        }

        sum += prio(both);
    }

    std::cout << sum << std::endl;
}
