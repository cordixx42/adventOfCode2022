#include <iostream>

bool inSprite(int sprite, int i) {
    if (abs(sprite - i) <= 1) {
        return true;
    }

    return false;
}

int main() {
    std::string line;

    std::string rows;

    int real = 1;
    int cycle = 0;

    int x = 1;

    // middle of the sprite, beginning 012
    int spritePos = 1;

    // int sum = 0;

    while (true) {
        if (real > 240) {
            break;
        }
        std::getline(std::cin, line);

        if (line == "quit") {
            break;
        }

        if (line == "noop") {
            cycle++;
            real++;
            // std::cout << "sprite " << spritePos << " cycle " << cycle << std::endl;
            if (inSprite(spritePos, cycle - 1)) {
                rows.append("#");
                // std::cout << "#" << std::endl;
            } else {
                // std::cout << "." << std::endl;
                rows.append(".");
            }
            if (cycle == 40) {
                rows.append("\n");
                cycle = 0;
                // std::cout << "cycle is " << cycle << " and x is " << x << std::endl;
                // sum += cycle * x;
            }

        } else {
            int value = stoi(line.substr(5));
            cycle++;
            real++;
            // std::cout << "sprite " << spritePos << " cycle " << cycle << std::endl;
            if (inSprite(spritePos, cycle - 1)) {
                rows.append("#");
                // std::cout << "#" << std::endl;
            } else {
                // std::cout << "." << std::endl;
                rows.append(".");
            }
            if (cycle == 40) {
                rows.append("\n");
                cycle = 0;
                // std::cout << "cycle is " << cycle << " and x is " << x << std::endl;
                // sum += cycle * x;
            }
            cycle++;
            real++;
            // std::cout << "sprite " << spritePos << " cycle " << cycle << std::endl;
            if (inSprite(spritePos, cycle - 1)) {
                rows.append("#");
                // std::cout << "#" << std::endl;
            } else {
                // std::cout << "." << std::endl;
                rows.append(".");
            }
            if (cycle == 40) {
                rows.append("\n");
                cycle = 0;
                // std::cout << "cycle is " << cycle << " and x is " << x << std::endl;
                // sum += cycle * x;
            }
            x += value;
            spritePos += value;
        }
    }

    std::cout << rows << std::endl;
}