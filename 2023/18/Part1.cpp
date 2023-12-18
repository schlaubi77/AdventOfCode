#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int shoelace(vector<pair<int, int>>& points, int perimeter) {
    int res = 0;
    for(int i = 0; i < points.size() - 1; i++) {
        res += (points[i].first * points[i + 1].second) - (points[i + 1].first * points[i].second);
    }
    return (abs(res) + perimeter) / 2 + 1;
}

int main() {
    fstream file("input.txt");
    string line;
    // first: row, second: col
    vector<pair<int, int>> points;
    pair<int, int> cur({0, 0});

    int circumference = 0;
    while (getline(file, line)) {
        int length = stoi(line.substr(2, 2));
        switch(line[0]) {
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