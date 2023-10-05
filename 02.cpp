#include <iostream>
#include <vector>

int gameResult(char other, char me) {
    if (other == 'A') {
        if (me == 'Y') {
            return 6;
        } else if (me == 'X') {
            return 3;
        } else {
            return 0;
        }
    }

    if (other == 'B') {
        if (me == 'Z') {
            return 6;
        } else if (me == 'Y') {
            return 3;
        } else {
            return 0;
        }
    }

    if (other == 'C') {
        if (me == 'X') {
            return 6;
        } else if (me == 'Z') {
            return 3;
        } else {
            return 0;
        }
    }
}

int played(char me) {
    if (me == 'X') {
        return 1;
    } else if (me == 'Y') {
        return 2;
    } else {
        return 3;
    }
}

int played2(char me) {
    if (me == 'A') {
        return 1;
    } else if (me == 'B') {
        return 2;
    } else {
        return 3;
    }
}

int outcome(char a) {
    if (a == 'X') {
        return 0;
    } else if (a == 'Y') {
        return 3;
    } else {
        return 6;
    }
}

// rock 1 A , paper 2 B, scissor 3 C

int step(char other, char outcome) {
    if (other == 'A') {
        if (outcome == 'X') {
            return played2('C');
            ;
        } else if (outcome == 'Y') {
            return played2(other);
        } else {
            return played2('B');
        }
    } else if (other == 'B') {
        if (outcome == 'X') {
            return played2('A');
            ;
        } else if (outcome == 'Y') {
            return played2(other);
        } else {
            return played2('C');
        }
    } else {
        if (outcome == 'X') {
            return played2('B');
            ;
        } else if (outcome == 'Y') {
            return played2(other);
        } else {
            return played2('A');
        }
    }
}

int main() {
    std::string line;

    // std::vector<char, char> input;

    int sum = 0;

    while (true) {
        std::getline(std::cin, line);

        // std::cout << line.at(0) << std::endl;
        // std::cout << line.at(2) << std::endl;

        if (line == "a") {
            break;
        }

        sum += step(line.at(0), line.at(2)) + outcome(line.at(2));
    }

    std::cout << sum << std::endl;
}