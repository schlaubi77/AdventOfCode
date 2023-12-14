#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> readFile() {
    fstream file("input.txt");
    string line;
    vector<string> platform;
    while(getline(file, line)) {
        platform.push_back(line);
    }
    return platform;
}

bool vecEquals(vector<string>& a, vector<string>& b) {
    if(a.size() != b.size()) {
        return false;
    }
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void moveUp(vector<string>& platform) {
    for(int i = 0; i < platform[0].length(); i++) {
        int movePos = 0;
        for(int j = 0; j < platform.size(); j++) {
            if(platform[j][i] == 'O') {
                if(movePos != j) {
                    platform[movePos][i] = 'O';
                    platform[j][i] = '.';
                }
                movePos++;
            } else if (platform[j][i] == '#') {
                movePos = j + 1;
            }
        }
    }
}

void moveDown(vector<string>& platform) {
    for(int i = 0; i < platform[0].length(); i++) {
        int movePos = platform.size() - 1;
        for(int j = platform.size() - 1; j >= 0; j--) {
            if(platform[j][i] == 'O') {
                if(movePos != j) {
                    platform[movePos][i] = 'O';
                    platform[j][i] = '.';
                }
                movePos--;
            } else if (platform[j][i] == '#') {
                movePos = j - 1;
            }
        }
    }
}

void moveLeft(vector<string>& platform) {
    for(int i = 0; i < platform.size(); i++) {
        int movePos = 0;
        for(int j = 0; j < platform[0].length(); j++) {
            if(platform[i][j] == 'O') {
                if(movePos != j) {
                    platform[i][movePos] = 'O';
                    platform[i][j] = '.';
                }
                movePos++;
            } else if (platform[i][j] == '#') {
                movePos = j + 1;
            }
        }
    }
}

void moveRight(vector<string>& platform) {
    for(int i = 0; i < platform.size(); i++) {
        int movePos = platform.size() - 1;
        for(int j = platform.size() - 1; j >= 0; j--) {
            if(platform[i][j] == 'O') {
                if(movePos != j) {
                    platform[i][movePos] = 'O';
                    platform[i][j] = '.';
                }
                movePos--;
            } else if (platform[i][j] == '#') {
                movePos = j - 1;
            }
        }
    }
}

void circle(vector<string>& platform) {
    moveUp(platform);
    moveLeft(platform);
    moveDown(platform);
    moveRight(platform);
}

int findLoad(vector<string>& platform) {
    int load = 0;
    for(int i = 0; i < platform[0].length(); i++) {
        for(int j = 0; j < platform.size(); j++) {
            if(platform[j][i] == 'O') {
                load += platform.size() - j;
            }
        }
    }
    return load;
}

int hashStringVector(vector<string>& vec) {
    hash<string> hasher;
    size_t seed = 0;
    for(string& str : vec) {
        seed ^= hasher(str) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

int main() {
    vector<string> platform = readFile();
    // find cyclic pattern in circeling
    map<int, int> circleHistory; // hash -> index
    int timesCircled = 0;
    while(circleHistory.count(hashStringVector(platform)) == 0) {
        circleHistory[hashStringVector(platform)] = timesCircled;
        circle(platform);
        timesCircled++;
    }
    // (num - before circle begins) % length of circle
    int equivalentCircles = (1000000000 - circleHistory[hashStringVector(platform)]) % (timesCircled - circleHistory[hashStringVector(platform)]);
    for(int i = 0; i < equivalentCircles; i++) {
        circle(platform);
    }
    cout << findLoad(platform) << endl;
}