
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <variant>
#include <vector>
// #include <fmt/core.h>

struct VList : std::variant<std::vector<VList>, int> {
   private:
    using base = std::variant<std::vector<VList>, int>;

   public:
    using base::base;
    VList(std::initializer_list<VList> vl) : base(vl) {}

    bool isVector() const { return std::holds_alternative<std::vector<VList>>(*this); }
    bool isInt() const { return std::holds_alternative<int>(*this); }

    auto* asVector() { return std::get_if<std::vector<VList>>(this); }
    auto* asInt() { return std::get_if<int>(this); }
};

enum class Order {
    right,
    wrong,
    undefined
};

// read line [1,[2],[3,[4,5]]]
VList parseLine(std::string line) {
    int bracket = 0;
    std::stack<VList> s;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '[') {
            s.push(VList{});
        } else if (std::isdigit(line[i])) {
            // int numLength = 1;
            int value = stoi(line.substr(i, 1));
            if (i < line.length() - 1 && std::isdigit(line[i + 1])) {
                value = 10;
            }

            std::cout << value << std::endl;
            if (s.top().isVector()) {
                std::cout << " top is vector" << std::endl;
                // s.top().asVector()->push_back(VList(value));
                auto& temp = s.top();
                //  std::cout << " am i adding ints" << std::endl;
                temp.asVector()->push_back(VList(value));
            }

        } else if (line[i] == ']') {
            if (s.size() == 1) {
                // std::cout << " return " << std::endl;
                return s.top();
            } else {
                auto top = s.top();
                s.pop();
                // std::cout << " push back top " << std::endl;
                s.top().asVector()->push_back(top);
            }
        } else {
            continue;
        }
    }
}

void printVList(VList l) {
    if (std::holds_alternative<int>(l)) {
        std::cout << *l.asInt() << std::endl;
    } else {
        std::cout << '[' << std::endl;
        for (int i = 0; i < l.asVector()->size(); i++) {
            printVList(l.asVector()->at(i));
        }
        std::cout << ']' << std::endl;
    }
}

Order correctOrder(VList& l1, VList& l2) {
    if (l1.isVector() && l2.isVector()) {
        std::cout << "case 1" << std::endl;
        auto s1 = l1.asVector()->size();
        auto s2 = l2.asVector()->size();

        for (int i = 0; i < s1; i++) {
            if (i >= s2) {
                // right side runs out of items first
                return Order::wrong;
            }
            auto res = correctOrder(l1.asVector()->at(i), l2.asVector()->at(i));
            if (res == Order::wrong || res == Order::right) {
                return res;
            }
        }

        if (s1 < s2) {
            return Order::right;
        }
        return Order::undefined;

    } else if (l1.isInt() && l2.isInt()) {
        std::cout << "case 2" << std::endl;
        std::cout << "two ints " << *l1.asInt() << " " << *l2.asInt() << std::endl;
        if (*l1.asInt() > *l2.asInt()) {
            return Order::wrong;
        } else if (*l1.asInt() < *l2.asInt()) {
            return Order::right;
        } else {
            return Order::undefined;
        }
    } else {
        std::cout << "case 3" << std::endl;
        if (l1.isInt()) {
            // promote l1 to list
            auto temp = VList{};
            temp.asVector()->push_back(VList(*l1.asInt()));
            return correctOrder(temp, l2);
        } else {
            auto temp = VList{};
            temp.asVector()->push_back(VList(*l2.asInt()));
            return correctOrder(l1, temp);
        }
    }
}

bool correct(VList& l1, VList& l2) {
    return correctOrder(l1, l2) == Order::right;
}

struct {
    bool operator()(VList& l1, VList& l2) const { return correctOrder(l1, l2) == Order::right; }
} comparator;

int main() {
    std::ifstream myfile;
    myfile.open("13.txt");

    if (!myfile.is_open()) {
        std::cout << "FILE NOT OPEN" << std::endl;
    }

    int index = 0;

    int sum = 0;

    std::string packet1;
    std::string packet2;

    std::vector<VList> all;

    auto divider1 = parseLine("[[2]]");
    auto divider2 = parseLine("[[6]]");

    all.push_back(divider1);
    all.push_back(divider2);

    while (!myfile.eof()) {
        std::getline(myfile, packet1);
        all.push_back(parseLine(packet1));
        std::getline(myfile, packet1);
        all.push_back(parseLine(packet1));
        if (!myfile.eof()) {
            std::getline(myfile, packet1);
        }
    }

    // std::cout << all.size() << std::endl;

    std::sort(all.begin(), all.end(), comparator);

    auto it1 = find(all.begin(), all.end(), divider1);
    auto it2 = find(all.begin(), all.end(), divider2);

    std::cout << (it1 - all.begin()) + 1 << std::endl;
    std::cout << (it2 - all.begin()) + 1 << std::endl;

    // printVList(all[301]);
}
