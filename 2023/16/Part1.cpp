#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<string> readFile() {
    ifstream file("input.txt");
    string line;
    vector<string> grid;
    while(getline(file, line)) {
        grid.push_back(line);
    }
    return grid;
}

set<int> beamStartsHandled;

int wrap(int y, int x, char direction) {
    return (direction << 16) + (y << 8) + x;
}

void moveBeam(vector<string>& grid, vector<vector<bool>>& energizationMap, int y, int x, char direction) {
    if(x < 0 || y < 0 || y >= grid.size() || x >= grid[0].length() || beamStartsHandled.count(wrap(y, x, direction)) > 0) {
        return;
    }
    beamStartsHandled.insert(wrap(y, x, direction));
    switch(direction) {
        case 'R':
            for(; x < grid[0].length(); x++) {
                energizationMap[y][x] = true;
                switch(grid[y][x]) {
                    case '/':
                        moveBeam(grid, energizationMap, y - 1, x, 'U');
                        return;
                    case '\\':
                        moveBeam(grid, energizationMap, y + 1, x, 'D');
                        return;
                    case '|':
                        moveBeam(grid, energizationMap, y - 1, x, 'U');
                        moveBeam(grid, energizationMap, y + 1, x, 'D');
                        return;
                }
            }
            return;
        case 'D':
            for(; y < grid.size(); y++) {
                energizationMap[y][x] = true;
                switch(grid[y][x]) {
                    case '/':
                        moveBeam(grid, energizationMap, y, x - 1, 'L');
                        return;
                    case '\\':
                        moveBeam(grid, energizationMap, y, x + 1, 'R');
                        return;
                    case '-':
                        moveBeam(grid, energizationMap, y, x + 1, 'R');
                        moveBeam(grid, energizationMap, y, x - 1, 'L');
                        return;
                }
            }
            return;
        case 'L':
            for(; x >= 0; x--) {
                energizationMap[y][x] = true;
                switch(grid[y][x]) {
                    case '/':
                        moveBeam(grid, energizationMap, y + 1, x, 'D');
                        return;
                    case '\\':
                        moveBeam(grid, energizationMap, y - 1, x, 'U');
                        return;
                    case '|':
                        moveBeam(grid, energizationMap, y - 1, x, 'U');
                        moveBeam(grid, energizationMap, y + 1, x, 'D');
                        return;
                }
            }
            return;
        case 'U':
            for(; y >= 0; y--) {
                energizationMap[y][x] = true;
                switch(grid[y][x]) {
                    case '/':
                        moveBeam(grid, energizationMap, y, x + 1, 'R');
                        return;
                    case '\\':
                        moveBeam(grid, energizationMap, y, x - 1, 'L');
                        return;
                    case '-':
                        moveBeam(grid, energizationMap, y, x - 1, 'L');
                        moveBeam(grid, energizationMap, y, x + 1, 'R');
                        return;
                }
            }
            return;
    }
}

int main() {
    vector<string> grid = readFile();
    vector<vector<bool>> energizationMap(grid.size(), vector<bool>(grid[0].length(), false));

    moveBeam(grid, energizationMap, 0, 0, 'R');

    int sumEnergized = 0;
    for(auto line : energizationMap) {
        for(bool entry : line) {
            if(entry) {
                sumEnergized++;
            }
        }
    }
    cout << sumEnergized << endl;
}