#include <stdlib.h>

#include <iostream>
#include <vector>

std::pair<int, int> goStep(const std::pair<int, int> head, std::pair<int, int> tail) {
    if (std::abs(tail.first - head.first) <= 1 && std::abs(tail.second - head.second) <= 1) {
        return tail;
    }

    if (head.second == tail.second) {
        if (head.first - tail.first == 2) {
            // go right tail
            tail.first++;
            return tail;
        } else if (head.first - tail.first == -2) {
            // go left tail
            tail.first--;
            return tail;
        }
    } else if (head.first == tail.first) {
        if (head.second - tail.second == 2) {
            // go up tail
            tail.second++;
            return tail;
        } else if (head.second - tail.second == -2) {
            // go down tail
            tail.second--;
            return tail;
        }
    }

    if (head.first > tail.first && head.second > tail.second) {
        tail.first++;
        tail.second++;
        return tail;
    } else if (head.first > tail.first && head.second < tail.second) {
        tail.first++;
        tail.second--;
        return tail;
    } else if (head.first < tail.first && head.second > tail.second) {
        tail.first--;
        tail.second++;
        return tail;
    } else if (head.first < tail.first && head.second < tail.second) {
        tail.first--;
        tail.second--;
        return tail;
    }
}

int main() {
    std::string line;

    // std::vector<std::vector<int>> field;

    int field[1000][1000];

    std::pair<int, int> indexHead(500, 500);

    std::pair<int, int> indexTail1(500, 500);
    std::pair<int, int> indexTail2(500, 500);
    std::pair<int, int> indexTail3(500, 500);
    std::pair<int, int> indexTail4(500, 500);
    std::pair<int, int> indexTail5(500, 500);
    std::pair<int, int> indexTail6(500, 500);
    std::pair<int, int> indexTail7(500, 500);
    std::pair<int, int> indexTail8(500, 500);
    std::pair<int, int> indexTail9(500, 500);

    std::vector<std::pair<int, int> > tails;
    //{indexHead, indexTail1, indexTail2, indexTail3, indexTail4, indexTail5, indexTail6, indexTail7, indexTail8, indexTail9};

    tails.push_back(indexHead);
    tails.push_back(indexTail1);
    tails.push_back(indexTail2);
    tails.push_back(indexTail3);
    tails.push_back(indexTail4);
    tails.push_back(indexTail5);
    tails.push_back(indexTail6);
    tails.push_back(indexTail7);
    tails.push_back(indexTail8);
    tails.push_back(indexTail9);

    field[500][500] = 1;

    int sum = 1;

    while (true) {
        std::getline(std::cin, line);
        // int index = line.find(' ');

        if (line == "quit") {
            break;
        }

        if (line.at(0) == 'R') {
            int value = stoi(line.substr(2));
            for (int i = 0; i < value; i++) {
                tails[0].first++;
                // std::cout << "head " << indexHead.first << " and " << indexHead.second << std::endl;
                for (int j = 0; j < 9; j++) {
                    auto result = goStep(tails[j], tails[j + 1]);
                    // std::cout << "tail" << result.first.first << " and " << result.first.second << std::endl;
                    tails[j + 1] = result;

                    // std::cout << "tail " << j + 1 << " " << result.first.first << " and " << result.first.second << std::endl;
                    if (j == 8) {
                        std::cout << "tail " << j + 1 << " " << result.first << " and " << result.second << std::endl;
                    }
                    if (j == 8 && field[result.first][result.second] != 1) {
                        field[result.first][result.second] = 1;
                        sum++;
                    }
                }
            }

        } else if (line.at(0) == 'L') {
            int value = stoi(line.substr(2));
            for (int i = 0; i < value; i++) {
                tails[0].first--;
                // std::cout << "head " << indexHead.first << " and " << indexHead.second << std::endl;
                for (int j = 0; j < 9; j++) {
                    auto result = goStep(tails[j], tails[j + 1]);
                    // std::cout << "tail" << result.first.first << " and " << result.first.second << std::endl;
                    tails[j + 1] = result;

                    // std::cout << "tail " << j + 1 << " " << result.first.first << " and " << result.first.second << std::endl;
                    if (j == 8) {
                        std::cout << "tail " << j + 1 << " " << result.first << " and " << result.second << std::endl;
                    }
                    if (j == 8 && field[result.first][result.second] != 1) {
                        field[result.first][result.second] = 1;
                        sum++;
                    }
                }
            }
        } else if (line.at(0) == 'U') {
            int value = stoi(line.substr(2));
            for (int i = 0; i < value; i++) {
                tails[0].second++;
                // std::cout << "loop" << std::endl;
                //  std::cout << "head " << indexHead.first << " and " << indexHead.second << std::endl;
                for (int j = 0; j < 9; j++) {
                    // std::cout << "before tails " << j << " " << tails[j].first << " " << tails[j].second << std::endl;
                    // std::cout << "before tails " << j + 1 << "  " << tails[j + 1].first << " " << tails[j + 1].second << std::endl;
                    auto result = goStep(tails[j], tails[j + 1]);
                    // std::cout << "after result " << result.first.first << " " << result.first.second << std::endl;
                    //  std::cout << "tail" << result.first.first << " and " << result.first.second << std::endl;
                    tails[j + 1] = result;

                    // std::cout << "tail " << j + 1 << " " << result.first.first << " and " << result.first.second << std::endl;
                    if (j == 8) {
                        std::cout << "tail " << j + 1 << " " << result.first << " and " << result.second << std::endl;
                    }
                    if (j == 8 && field[result.first][result.second] != 1) {
                        field[result.first][result.second] = 1;
                        sum++;
                    }
                }
            }
        } else {
            int value = stoi(line.substr(2));
            for (int i = 0; i < value; i++) {
                tails[0].second--;
                // std::cout << "head " << indexHead.first << " and " << indexHead.second << std::endl;
                for (int j = 0; j < 9; j++) {
                    // std::cout << "before tails[j] " << tails[j].first << " " << tails[j].second << std::endl;
                    // std::cout << "before tails[j+1] " << tails[j + 1].first << " " << tails[j + 1].second << std::endl;
                    auto result = goStep(tails[j], tails[j + 1]);
                    // std::cout << "after result " << result.first.first << " " << result.first.second << std::endl;
                    //  std::cout << "tail" << result.first.first << " and " << result.first.second << std::endl;
                    tails[j + 1] = result;
                    // std::cout << "tail " << j + 1 << " " << result.first.first << " and " << result.first.second << std::endl;
                    if (j == 8) {
                        std::cout << "tail " << j + 1 << " " << result.first << " and " << result.second << std::endl;
                    }
                    if (j == 8 && field[result.first][result.second] != 1) {
                        field[result.first][result.second] = 1;
                        sum++;
                    }
                }
            }
        }
    }

    std::cout << sum << std::endl;
}
