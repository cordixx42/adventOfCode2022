#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main() {
    std::ifstream myfile;
    myfile.open("11.txt");

    if (!myfile.is_open()) {
        std::cout << "FILE NOT OPEN" << std::endl;
    }

    // system("stty raw");
    std::vector<std::queue<long>> monkeys;
    monkeys.reserve(7);

    std::vector<std::function<int(long)>> operations;
    std::vector<std::function<void(long)>> test;

    std::vector<int> inspections;
    for (int i = 0; i < 8; i++) {
        inspections.push_back(0);
    }

    std::string line;

    int numMonkeys = 8;
    int index = -1;

    int mod = 9699690;

    // read everything
    for (int i = 0; i < numMonkeys; i++) {
        std::cout << "loop " << i << std::endl;
        std::getline(myfile, line);  // Monkey or empty line
        // std::getline (myfile, myline);

        // lines with item
        std::getline(myfile, line);
        index = line.find(':');
        // read in correct items
        for (int j = 2; index + j < line.length(); j += 4) {
            // std::cout << index + j << std::endl;
            monkeys[i].push(((int)stoi(line.substr(index + j, 2))));
        }

        // std::cout << "q" << std::endl;
        std::cout << "hereeee" << std::endl;
        // get operation
        std::getline(myfile, line);

        if (i == 1) {
            operations.push_back([mod](long old) { return ((old * old) % mod); });
        } else {
            index = line.find('=');
            char op = line.at(index + 6);
            int operand = stoi(line.substr(index + 8));
            // std::cout << "qq" << std::endl;
            if (op == '*') {
                operations.push_back([mod, operand](long old) { return (old * (operand % mod)) % mod; });
            } else if (op == '+') {
                operations.push_back([mod, operand](long old) { return (old + (operand % mod)) % mod; });
            } else if (op == '-') {
                operations.push_back([mod, operand](long old) { return (old - (operand % mod)) % mod; });
                // } else {
                //     std::cout << "is there a div ????" << std::endl;
                //     operations.push_back([mod, operand](int old) { return modDivide(old, operand, mod); });
                // }
            } else {
                std::cout << "NoooooooOOOOOOO" << std::endl;
            }
        }

        // get test
        // std::cout << "index " << index << " line " << line << std::endl;
        std::getline(myfile, line);
        index = line.find('y');
        // std::cout << "index " << index << " line " << line << std::endl;
        int operand = stoi(line.substr(index + 2));
        // std::cout << "get test" << std::endl;
        //  true case
        std::getline(myfile, line);
        index = line.find('y');
        int monkeyTrue = stoi(line.substr(index + 2));
        // std::cout << "true case" << std::endl;
        //  false case
        std::getline(myfile, line);
        index = line.find('y');
        int monkeyFalse = stoi(line.substr(index + 2));
        // std::cout << "false test" << std::endl;

        std::cout << "hereeee" << std::endl;
        test.push_back([mod, &monkeys, operand, monkeyTrue, monkeyFalse](long value) { ((value + mod) % operand) == 0 ? monkeys[monkeyTrue].push(value) : monkeys[monkeyFalse].push(value); });

        if (i == numMonkeys - 1) {
            break;
        }
        std::getline(myfile, line);
    }

    std::cout << "reading done" << std::endl;
    // for all rounds
    for (int i = 0; i < 10000; i++) {
        // std::cout << "i = " << i << std::endl;
        //  for all monkeys
        for (int j = 0; j < numMonkeys; j++) {
            // for all items
            int sizeBefore = monkeys[j].size();
            for (int k = 0; k < sizeBefore; k++) {
                long item = monkeys[j].front();
                monkeys[j].pop();
                // std::cout << "get Item " << item << std::endl;
                item = operations[j](item);
                // std::cout << "do operation " << item << std::endl;
                // item = item / 3;
                // std::cout << "divide 3 " << item << std::endl;
                test[j](item);
                // std::cout << "test " << item << std::endl;
                inspections[j]++;
            }
        }
        if (i == 0 || i == 19 || i == 999 || i == 1999 || i == 9999) {
            for (int a = 0; a < numMonkeys; a++) {
                std::cout << inspections[a] << std::endl;
            }
        }

        if (i <= 20) {
            std::cout << "round " << i << std::endl;
            for (int a = 0; a < numMonkeys; a++) {
                std::cout << inspections[a] << std::endl;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        std::cout << inspections[i] << std::endl;
    }
}