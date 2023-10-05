#include <iostream>
#include <vector>

bool isVisible(int x, int y, std::vector<std::string> trees, int maxX, int maxY) {
    if (x == 0 || y == 0 || x == maxX || y == maxY) {
        return true;
    }

    bool result = true;

    // check horizontally left
    std::string row = trees[y];
    for (int i = 0; i < x; i++) {
        if ((row[i] >= row[x])) {
            result = false;
            break;
        }
    }

    if (result) {
        return true;
    }

    result = true;

    // check horizontally right
    for (int i = x + 1; i <= maxX; i++) {
        if ((row[i] >= row[x])) {
            result = false;
            break;
        }
    }

    if (result) {
        return true;
    }

    result = true;

    // check vertically top
    for (int i = 0; i < y; i++) {
        if (trees[i].at(x) >= trees[y].at(x)) {
            result = false;
            break;
        }
    }

    if (result) {
        return true;
    }

    result = true;

    // check vertically bottom
    for (int i = y + 1; i <= maxY; i++) {
        if (trees[i].at(x) >= trees[y].at(x)) {
            result = false;
            break;
        }
    }

    if (result) {
        return true;
    }

    return false;
}

int scenicScore(int x, int y, std::vector<std::string> trees, int maxX, int maxY) {
    int left = 0;

    // check horizontally left
    std::string row = trees[y];
    for (int i = x - 1; i >= 0; i--) {
        if ((row[i] >= row[x])) {
            left++;
            break;
        } else {
            left++;
        }
    }

    int right = 0;

    // check horizontally right
    for (int i = x + 1; i <= maxX; i++) {
        if ((row[i] >= row[x])) {
            right++;
            break;
        } else {
            right++;
        }
    }

    int top = 0;
    // check vertically top
    for (int i = y - 1; i >= 0; i--) {
        if (trees[i].at(x) >= trees[y].at(x)) {
            top++;
            break;
        } else {
            top++;
        }
    }

    int bottom = 0;

    // check vertically bottom
    for (int i = y + 1; i <= maxY; i++) {
        if (trees[i].at(x) >= trees[y].at(x)) {
            bottom++;
            break;
        } else {
            bottom++;
        }
    }

    return left * right * top * bottom;
}

int main() {
    // std::vector<std::vector<int> > trees;
    std::vector<std::string> trees;

    std::string line;
    char c;

    while (true) {
        std::getline(std::cin, line);
        if (line == "quit") {
            break;
        }
        trees.push_back(line);
        // for (int i = 0; i < line.length(); i++) {
        //     trees[i].push_back(ctoi(line[i]));
        // }
    }

    int maxX = trees[0].length() - 1;
    int maxY = trees.size() - 1;

    int edges = (maxX + 1) * 2 + (maxY - 1) * 2;

    int sum = 0;

    for (int x = 1; x < maxX; x++) {
        for (int y = 1; y < maxY; y++) {
            if (isVisible(x, y, trees, maxX, maxY)) {
                sum += 1;
            }
        }
    }

    std::cout << sum + edges << std::endl;

    int scene = 0;
    int max = 0;

    for (int x = 0; x <= maxX; x++) {
        for (int y = 0; y <= maxY; y++) {
            int next = scenicScore(x, y, trees, maxX, maxY);
            if (next > max) {
                max = next;
            }
        }
    }

    std::cout << max << std::endl;
}