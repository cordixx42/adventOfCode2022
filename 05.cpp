#include <iostream>
#include <vector>

int main() {
    std::string line;

    std::vector<char> stack1;
    std::vector<char> stack2;
    std::vector<char> stack3;
    std::vector<char> stack4;
    std::vector<char> stack5;
    std::vector<char> stack6;
    std::vector<char> stack7;
    std::vector<char> stack8;
    std::vector<char> stack9;

    std::vector<std::vector<char> > all;
    all.push_back(stack1);
    all.push_back(stack2);
    all.push_back(stack3);
    all.push_back(stack4);
    all.push_back(stack5);
    all.push_back(stack6);
    all.push_back(stack7);
    all.push_back(stack8);
    all.push_back(stack9);

    while (true) {
        std::getline(std::cin, line);
        if (line.at(1) == '1') {
            break;
        }
        for (int i = 0; i < 9; i++) {
            // std::cout << "Now round " + i << std::endl;
            if (line.length() <= (i * 4 + 1)) {
                continue;
            }
            if (line.at(i * 4 + 1) >= 65 && line.at(i * 4 + 1) <= 90) {
                // std::cout << line.at((i - 1) * 4 + 1) << std::endl;
                all.at(i).insert(all.at(i).begin(), line.at(i * 4 + 1));
                // all.at(i).push_back('A');
            }
        }
    }

    // empty line
    std::getline(std::cin, line);

    while (true) {
        std::getline(std::cin, line);
        if (line == "quit") {
            break;
        }
        int whereMove = line.find('e');
        int whereFrom = line.find('f');
        int whereFromLast = line.find_last_of('m');
        int whereTo = line.find('t');

        // std::cout << "first" + line.substr(whereMove + 2, whereFrom - whereMove - 3) << std::endl;
        int first = stoi(line.substr(whereMove + 2, whereFrom - whereMove - 3));
        // std::cout << "second" + line.substr(whereFromLast + 2, whereTo - whereFromLast - 3) << std::endl;
        int snd = stoi(line.substr(whereFromLast + 2, whereTo - whereFromLast - 3));
        // std::cout << "third" + line.substr(whereTo + 3) << std::endl;
        int third = stoi(line.substr(whereTo + 3, line.length() - 5 - whereTo));

        for (int i = 0; i < first; i++) {
            char elem = all.at(snd - 1).back();
            // std::cout << elem << std::endl;
            all.at(third - 1).insert(all.at(third - 1).begin() + all.at(third - 1).size() - i, elem);
            all.at(snd - 1).pop_back();
        }
    }

    for (int i = 0; i < 9; i++) {
        std::cout << all.at(i).back() << std::endl;
    }
}
