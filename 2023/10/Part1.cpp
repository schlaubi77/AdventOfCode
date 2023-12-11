#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char from = '0';

pair<vector<string>, pair<int, int>> readFile() {
    ifstream file("input.txt");
    string line;
    vector<string> grid;
    pair<int, int> start;
    while(getline(file, line)) {
        if(line.find('S') != string::npos) {
            start = make_pair(grid.size(), line.find('S'));
        }
        grid.push_back(line);
    }
    return make_pair(grid, start);
}

pair<int, int> findNext(vector<string> grid, int y, int x) {
    switch(grid[y][x]) {
        case '|':
            if(from == 'U') {
                return make_pair(y + 1, x);
            } else {
                return make_pair(y - 1, x);
            }
        case '-':
            if(from == 'L') {
                return make_pair(y, x + 1);
            } else {
                return make_pair(y, x - 1);
            }
        case 'L':
            if(from == 'U') {
                from = 'L';
                return make_pair(y, x + 1);
            } else {
                from = 'D';
                return make_pair(y - 1, x);
            }
        case 'J':
            if(from == 'U') {
                from = 'R';
                return make_pair(y, x - 1);
            } else {
                from = 'D';
                return make_pair(y - 1, x);
            }
        case '7':
            if(from == 'D') {
                from = 'R';
                return make_pair(y, x - 1);
            } else {
                from = 'U';
                return make_pair(y + 1, x);
            }
        case 'F':
            if(from == 'D') {
                from = 'L';
                return make_pair(y, x + 1);
            } else {
                from = 'U';
                return make_pair(y + 1, x);
            }
    }
    cout << "ERROR" << endl;
    return make_pair(-1, -1);
}

int main() {
    pair<vector<string>, pair<int, int>> p = readFile();
    vector<string> grid = p.first;
    int y = p.second.first; // y, x
    int x = p.second.second;

    x--; from = 'R'; // manual first step
    

    int steps = 1;
    while(grid[y][x] != 'S') {
        steps++;
        pair<int, int> pos = findNext(grid, y, x);
        y = pos.first;
        x = pos.second;
        
    }

    cout << steps / 2 << endl;
}