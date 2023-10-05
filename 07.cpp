#include <iostream>
#include <vector>

class Dir {
   public:
    bool isDir;
    std::string name;
    int size;
    std::vector<Dir> subdir;
    Dir* parent;

    Dir(bool a, std::string b, int c, Dir* e) {
        isDir = a;
        name = b;
        size = c;
        subdir = std::vector<Dir>();
        parent = e;
    }
};

// recursively update parent size
void updateParent(Dir* current, int size) {
    while (current->parent != NULL) {
        current = current->parent;
        current->size += size;
    }
}

void addToVector(int& sum, Dir* root) {
    if (!root->isDir) {
        return;
    }
    if (root->size <= 100000) {
        sum += root->size;
    }
    for (int i = 0; i < root->subdir.size(); i++) {
        addToVector(sum, &(root->subdir[i]));
    }
}

void findLeastDir(Dir* root, int least, int& max) {
    if (!root->isDir) {
        return;
    }

    if (root->size >= least && root->size < max) {
        max = root->size;
    }
    for (int i = 0; i < root->subdir.size(); i++) {
        findLeastDir(&(root->subdir[i]), least, max);
    }
}

int main() {
    Dir root = Dir(true, "/", 0, NULL);

    Dir& current = root;

    std::string line;

    bool ls = false;
    std::string lsline;

    std::getline(std::cin, line);

    // std::cout << "first line skipped" << std::endl;

    while (true) {
        if (ls) {
            line = lsline;
            ls = false;
        } else {
            std::getline(std::cin, line);
            if (line == "quit") {
                break;
            }
        }

        // cd case
        if (line.at(2) == 'c') {
            // std::cout << "case cd" << std::endl;
            //  cd /
            if (line.at(5) == '/') {
                // std::cout << "case cd /" << std::endl;

                current = root;
            } else if (line.at(5) == '.') {
                // std::cout << "case cd .." << std::endl;

                // std::cout << current->parent << std::endl;
                current = *(current.parent);
            } else {
                // std::cout << "case cd <name>" << std::endl;

                std::string name = line.substr(5, line.length() - 5);
                // std::cout << name << std::endl;

                for (int i = 0; i < current.subdir.size(); i++) {
                    if (current.subdir[i].name == name) {
                        // std::cout << "yessssss i got into subdirectory" << std::endl;

                        current = (current.subdir[i]);
                        break;
                    }
                }
                // Dir sub = Dir(true, name, 0, new std::vector<Dir>, current);
                // current.subdir.push_back(sub);
                // current = sub;
            }
        }
        // ls case
        else if (line.at(2) == 'l') {
            // std::cout << "ls " << std::endl;

            line = "abc";
            // std::cout << "abc" << std::endl;
            while (line.at(0) != '$') {
                // std::cout << "def" << std::endl;
                std::getline(std::cin, line);

                if (line == "quit") {
                    break;
                }

                if (line.at(0) == '$') {
                    ls = true;
                    lsline = line;
                    break;
                }

                //  dir
                if (line.at(0) == 'd') {
                    // std::cout << "dir ..." << std::endl;

                    std::string name = line.substr(4, line.length() - 4);
                    Dir sub = Dir(true, name, 0, current);
                    current.subdir.push_back(sub);
                }
                // 123 a.txt
                else {
                    // std::cout << "234 ..." << std::endl;

                    int space = line.find(' ');
                    // std::cout << space << std::endl;
                    int size = stoi(line.substr(0, space));
                    std::string name = line.substr(space + 1, line.length() - space - 1);
                    Dir sub = Dir(false, name, size, current);
                    current.subdir.push_back(sub);
                    updateParent(&sub, size);
                }
            }
        }
    }

    // part 2
    int used = root.size;

    std::cout << root.size << std::endl;

    int atLeastNeeded = 30000000 - (70000000 - used);

    int max = used;

    findLeastDir(&root, atLeastNeeded, max);

    std::cout << max << std::endl;
    // std::cout << atLeastNeeded << std::endl;

    // std::cout << diff << std::endl;
}
