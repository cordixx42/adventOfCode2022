#include <fstream>
#include <iostream>
#include <vector>

enum class Material {
    rock,
    air,
    sand,
    sunkSand
};

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

void printField(std::vector<std::vector<Material>> field) {
    for (int i = 0; i < field.size(); i++) {
        std::cout << i;
    }

    for (int j = 0; j < field[0].size(); j++) {
        std::cout << j;
        for (int i = 0; i < field.size(); i++) {
            if (i + 494 == 500 && j == 0) {
                std::cout << '+';
            } else {
                switch (field[i][j]) {
                    case Material::rock:
                        std::cout << '#';
                        break;
                    case Material::air:
                        std::cout << '.';
                        break;
                    case Material::sand:
                        std::cout << 'o';
                        break;
                    case Material::sunkSand:
                        std::cout << '&';
                        break;
                }
            }
        }
        std::cout << "\n";
    }
}

void putSandCorn(std::vector<std::vector<Material>>& field) {
    int x = 500 - 494;
    int y = 0;

    while (true) {
        if (field.at(x).at(y + 1) == Material::air) {
            y++;
        } else if (field.at(x - 1).at(y + 1) == Material::air) {
            x--;
            y++;
        } else if (field.at(x + 1).at(y + 1) == Material::air) {
            x++;
            y++;
        } else {
            if (field[x][y] != Material::air) {
                throw std::out_of_range("ooo");
            }
            field[x][y] = Material::sunkSand;

            // std::cout << "x " << x << std::endl;
            // std::cout << "y " << y << std::endl;
            break;
        }
    }
}

int main() {
    std::ifstream myfile;
    myfile.open("14.txt");

    if (!myfile.is_open()) {
        std::cout << "FILE NOT OPEN" << std::endl;
    }

    int rows = 10;
    int columns = 10;

    int max = 0;
    int min = 800;

    // std::vector<std::vector<Material>> field;
    // field.resize(columns);

    std::vector<std::vector<Material>> field(columns, std::vector<Material>(rows, Material::air));

    std::string line;

    while (!myfile.eof()) {
        std::getline(myfile, line);
        std::string delimiter = " -> ";
        std::vector<std::string> splitted = split(line, delimiter);
        for (int i = 0; i < splitted.size() - 1; ++i) {
            std::cout << "Loop" << std::endl;
            int index = splitted[i].find(',');
            int x1 = stoi(splitted[i].substr(0, index));

            int y1 = stoi(splitted[i].substr(index + 1, splitted[i].length() - index - 1));
            // if (y1 > max) {
            //     max = y1;
            // }

            // if (y1 < min) {
            //     min = y1;
            // }
            index = splitted[i + 1].find(',');
            int x2 = stoi(splitted[i + 1].substr(0, index));

            int y2 = stoi(splitted[i + 1].substr(index + 1, splitted[i].length() - index - 1));

            int xstart{};
            int xend{};

            if (x1 > x2) {
                xstart = x2;
                xend = x1;
            } else {
                xstart = x1;
                xend = x2;
            }

            int ystart{};
            int yend{};

            if (y1 > y2) {
                ystart = x2;
                yend = y1;
            } else {
                ystart = y1;
                yend = y2;
            }

            for (int x = xstart; x <= xend; x++) {
                for (int y = ystart; y <= yend; y++) {
                    field[x - 494][y] = Material::rock;
                }
            }

            // std::cout << x << std::endl;
            // std::cout << y << std::endl;
            // field[x - 483][y] = Material::rock;
        }
    }

    std::cout << " reading finished " << std::endl;
    std::cout << "max " << max << std::endl;
    std::cout << "min " << min << std::endl;
    // printField(field);

    printField(field);

    int count = 0;

    while (true) {
        std::cout << "put corn" << std::endl;
        std::cout << count << std::endl;

        try {
            putSandCorn(field);
            printField(field);

            count++;
        } catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
            break;
        }
    }

    std::cout << count << std::endl;
}