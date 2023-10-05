#include <iostream>
#include <vector>

int main() {
    std::string line;
    int sum = 0;

    while (true) {
        std::getline(std::cin, line);

        if (line == "a") {
            break;
        }

        int whereComma = line.find(',');
        int firstDash = line.find_first_of('-');
        int lastDash = line.find_last_of('-');

        int fstBegin = stoi(line.substr(0, firstDash));
        int fstEnd = stoi(line.substr(firstDash + 1, whereComma - firstDash - 1));
        int sndBegin = stoi(line.substr(whereComma + 1, lastDash - whereComma - 1));
        int sndEnd = stoi(line.substr(lastDash + 1, line.length() - lastDash - 1));

        if ((fstBegin < sndBegin && fstEnd < sndBegin) || (sndBegin < fstBegin && sndEnd < fstBegin)) {
            continue;
        } else {
            ++sum;
        }
    }

    std::cout << sum << std::endl;
}