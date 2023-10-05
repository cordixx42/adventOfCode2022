#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int manhattan(std::pair<int, int> pos1, std::pair<int, int> pos2) {
    return (abs(pos1.first - pos2.first)) + (abs(pos1.second - pos2.second));
}

int deltaX(int manhattan, std::pair<int, int> sensor) {
    return manhattan - abs(sensor.second - 2000000);
}

int delta(int manhattan, std::pair<int, int> sensor, int y) {
    return manhattan - abs(sensor.second - y);
}

void insertDumb(std::vector<std::unordered_set<int>>& ranges, int line, int x, int delta) {
    int xstart = x - delta;
    if (xstart < 0) {
        xstart = 0;
    }
    int xend = x + delta;
    if (xend > 4000000) {
        xend = 4000000;
    }
    for (int i = xstart; i <= xend; i++) {
        ranges[line].insert(i);
    }
}

void insertRange(std::vector<std::vector<std::pair<int, int>>>& ranges, int line, int x, int delta) {
    int xstart = x - delta;
    if (xstart < 0) {
        xstart = 0;
    }
    int xend = x + delta;
    if (xend > 4000000) {
        xend = 4000000;
    }

    // case empty
    if (ranges[line].empty()) {
        ranges[line].push_back(std::make_pair(xstart, xend));
    }

    int n = ranges[line].size();
    int leftIndex = -1;
    int rightIndex = -1;

    for (int i = 0; i < n; i++) {
        if (leftIndex > 0 && rightIndex > 0) {
            break;
        }

        if (xstart < 0 && xstart <= ranges[line][i].second) {
            leftIndex = i;
        }

        if (xend < 0 && xend >= ranges[line][i].first) {
            rightIndex = i;
        }
    }

    // range inside existing range, nothing has to be changed
    if (leftIndex == rightIndex && xend <= ranges[line][leftIndex].second && xstart >= ranges[line][leftIndex].first) {
        return;
    }
}

int main() {
    std::ifstream myfile;
    myfile.open("15.txt");

    if (!myfile.is_open()) {
        std::cout << "FILE NOT OPEN" << std::endl;
    }

    int minX = 0;
    int maxX = 0;
    int minY = 0;
    int maxY = 0;

    std::string line;

    std::vector<std::pair<int, int>> sensors;

    std::vector<std::pair<int, int>> beacons;

    std::vector<int> manhattans;

    // std::unordered_map<int, std::pair<int, int>> sensor2beacon;

    for (int i = 0; i < 27; i++) {
        std::getline(myfile, line);

        int sensorX = 0;
        int sensorY = 0;
        int beaconX = 0;
        int beaconY = 0;

        int firstx = line.find('x');
        int firsty = line.find('y');
        int firstcolon = line.find(':');
        int firstcomma = line.find(',');

        sensorX = stoi(line.substr(firstx + 2, firstcomma - firstx - 2));
        sensorY = stoi(line.substr(firsty + 2, firstcolon - firsty - 2));

        firstx = line.find_last_of('x');
        firsty = line.find_last_of('y');
        firstcolon = line.length();
        firstcomma = line.find_last_of(',');

        beaconX = stoi(line.substr(firstx + 2, firstcomma - firstx - 2));
        beaconY = stoi(line.substr(firsty + 2, firstcolon - firsty - 2));

        sensors.push_back(std::make_pair(sensorX, sensorY));
        beacons.push_back(std::make_pair(beaconX, beaconY));
        manhattans.push_back(manhattan(std::make_pair(sensorX, sensorY), std::make_pair(beaconX, beaconY)));

        if (sensorX > maxX) {
            maxX = sensorX;
        }
        if (beaconX > maxX) {
            maxX = beaconX;
        }
        if (sensorX < minX) {
            minX = sensorX;
        }
        if (beaconX < minX) {
            minX = beaconX;
        }
        if (sensorY > maxY) {
            maxY = sensorY;
        }
        if (beaconY > maxY) {
            maxY = beaconY;
        }
        if (sensorY < minY) {
            minY = sensorY;
        }
        if (beaconY < minY) {
            minY = beaconY;
        }

        // std::cout << sensorX << " " << sensorY << std::endl;
        // std::cout << beaconX << " " << beaconY << std::endl;
    }

    std::unordered_set<int> allXfixedY;

    for (int i = 0; i < manhattans.size(); i++) {
        int delta = deltaX(manhattans[i], sensors[i]);
        if (delta < 0) {
            continue;
        }
        for (int j = sensors[i].first - delta; j <= sensors[i].first + delta; j++) {
            allXfixedY.insert(j);
        }
    }

    std::cout << allXfixedY.size();

    // part2

    for (int i = 0; i < 4000001; i++) {
        std::cout << ".";
    }
}