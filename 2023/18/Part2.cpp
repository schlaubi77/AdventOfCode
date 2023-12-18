#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int64_t shoelace(vector<pair<int64_t, int64_t>>& points, int64_t perimeter) {
    int64_t res = 0;
    for(int i = 0; i < points.size() - 1; i++) {
        res += (points[i].first * points[i + 1].second) - (points[i + 1].first * points[i].second);
    }
    return (abs(res) + perimeter) / 2 + 1;
}

vector<pair<char, int>> readFile() {
    fstream file("input.txt");
    string line;
    vector<pair<char, int>> instructions;
    char toChar[] = { 'R', 'D', 'L', 'U'};
    while (getline(file, line)) {
        int len = line.length();
        instructions.push_back({toChar[line[len - 2] - '0'], stoi(line.substr(len - 7, 5), nullptr, 16)});
    }
    return instructions;
}

int main() {
    // first: row, second: col
    vector<pair<int64_t, int64_t>> points;
    pair<int64_t, int64_t> cur({0, 0});

    int64_t circumference = 0;
    for (auto& instruct : readFile()) {
        int64_t length = instruct.second;
        switch(instruct.first) {
        case 'U':
            cur.first -= length;
            break;
        case 'D':
            cur.first += length;
            break;
        case 'R':
            cur.second += length;
            break;
        case 'L':
            cur.second -= length;
            break;
        }
        points.push_back(cur);
        circumference += length;
    }
    cout << shoelace(points, circumference) << endl;
}