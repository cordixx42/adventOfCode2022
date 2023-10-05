#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

bool up(std::pair<int, int> pos, std::vector<std::vector<char>> field) {
    if ((pos.first - 1 < 0) || (field[pos.first - 1][pos.second] > field[pos.first][pos.second] + 1)) {
        return false;
    }
    return true;
}

bool down(std::pair<int, int> pos, std::vector<std::vector<char>> field) {
    if ((pos.first + 1 >= field.size()) || (field[pos.first + 1][pos.second] > field[pos.first][pos.second] + 1)) {
        return false;
    }
    return true;
}

bool right(std::pair<int, int> pos, std::vector<std::vector<char>> field) {
    if ((pos.second + 1 >= field[0].size()) || (field[pos.first][pos.second + 1] > field[pos.first][pos.second] + 1)) {
        return false;
    }
    return true;
}

bool left(std::pair<int, int> pos, std::vector<std::vector<char>> field) {
    if ((pos.second - 1 < 0) || (field[pos.first][pos.second - 1] > field[pos.first][pos.second] + 1)) {
        return false;
    }
    return true;
}

struct Node {
    std::pair<int, int> elem;
    int level;

    Node(std::pair<int, int> e, int l) {
        elem = e;
        level = l;
    }
};

bool pairInList(std::pair<int, int> p, std::vector<Node> list) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].elem.first == p.first && list[i].elem.second == p.second) {
            return true;
        }
    }
    return false;
}

int BFS(std::pair<int, int> start, std::pair<int, int> end, std::vector<std::vector<char>> field) {
    std::queue<Node> queue;
    std::vector<Node> list;
    list.push_back(Node(start, 0));
    queue.push(Node(start, 0));

    int counter = 0;

    while (!queue.empty()) {
        Node node = queue.front();
        std::pair<int, int> top = node.elem;
        std::cout << top.first << " " << top.second << std::endl;
        std::cout << node.level << std::endl;
        queue.pop();
        // if (top.first == end.first && top.second == end.second) {
        //     std::cout << "yeah" << std::endl;
        //     return node.level;
        // }

        if (field[top.first][top.second] == 'z') {
            std::cout << "yeah" << std::endl;
            return node.level;
        }

        // std::cout << "Here" << std::endl;

        std::pair<int, int> upp = std::make_pair(top.first - 1, top.second);
        if (up(top, field) && !pairInList(upp, list)) {
            queue.push(Node(upp, node.level + 1));
            list.push_back(Node(upp, node.level + 1));
        }

        std::pair<int, int> downn = std::make_pair(top.first + 1, top.second);
        if (down(top, field) && !pairInList(downn, list)) {
            queue.push(Node(downn, node.level + 1));
            list.push_back(Node(downn, node.level + 1));
        }

        std::pair<int, int> rightt = std::make_pair(top.first, top.second + 1);
        if (right(top, field) && !pairInList(rightt, list)) {
            queue.push(Node(rightt, node.level + 1));
            list.push_back(Node(rightt, node.level + 1));
        }
        std::pair<int, int> leftt = std::make_pair(top.first, top.second - 1);
        if (left(top, field) && !pairInList(leftt, list)) {
            queue.push(Node(leftt, node.level + 1));
            list.push_back(Node(leftt, node.level + 1));
        }
    }

    return counter;
}

void changeField(std::vector<std::vector<char>>& field) {
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[0].size(); j++) {
            field[i][j] = static_cast<char>(97 + 25 - (field[i][j] - 97));
        }
    }
}

int main() {
    std::ifstream myfile;
    myfile.open("12.txt");

    if (!myfile.is_open()) {
        std::cout << "FILE NOT OPEN" << std::endl;
    }
    int rows = 41;
    int cols = 179;

    std::vector<std::vector<char>> field;
    field.resize(rows);

    std::pair<int, int> startS{0, 0};
    std::pair<int, int> endE{0, 0};

    std::string line;

    for (int i = 0; i < rows; i++) {
        std::getline(myfile, line);
        for (int j = 0; j < line.length(); j++) {
            field[i].push_back(line.at(j));
            if (line.at(j) == 'S') {
                startS.first = i;
                startS.second = j;
            } else if (line.at(j) == 'E') {
                endE.first = i;
                endE.second = j;
            }
        }
    }

    // std::cout << line.length() << std::endl;

    field[startS.first].at(startS.second) = 'a';
    field[endE.first].at(endE.second) = 'z';

    changeField(field);

    std::cout << BFS(endE, startS, field) << std::endl;
}