#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SIZE 140

using namespace std;

int manhattenDist(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pair<int, int>> readFile() {
    vector<pair<int, int>> galaxies;
    ifstream file("input.txt");
    string line;
    int y = 0;

    bool galaxiesY[SIZE] = {0};
    bool galaxiesX[SIZE] = {0};
    while(getline(file, line)) {
        int idx = 0;
        while(line.find('#', idx) != string::npos) {
            idx = line.find('#', idx);
            galaxies.push_back(make_pair(y, idx));
            galaxiesX[idx] = true;
            idx++; 
            galaxiesY[y] = true;
            
        }
        y++;
    }
    int curOffset = 0;
    for(int i = 0; i < SIZE; i++) {
        if(!galaxiesY[i]) {
            for(int j = 0; j < galaxies.size(); j++) {
                if(galaxies[j].first > i + curOffset) {
                    galaxies[j].first++;
                }
            }
            curOffset++;
        }
    }
    curOffset = 0;
    for(int i = 0; i < SIZE; i++) {
        if(!galaxiesX[i]) {
            for(int j = 0; j < galaxies.size(); j++) {
                if(galaxies[j].second > i + curOffset) {
                    galaxies[j].second++;
                }
            }
            curOffset++;
        }
    }
    return galaxies;
}

int main() {
    vector<pair<int, int>> galaxies = readFile();
    int totalDist = 0;
    for(int i = 0; i < galaxies.size(); i++) {
        for(int j = i + 1; j < galaxies.size(); j++) {
            totalDist += manhattenDist(galaxies[i], galaxies[j]);
        }
    }
    cout << totalDist << endl;
    /*
    for(int i = 0; i < galaxies.size(); i++) {
        cout << galaxies[i].first << " " << galaxies[i].second << endl;
    }
    */
    return 0;
}