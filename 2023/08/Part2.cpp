#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    while(b != 0) {
        int64_t tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int64_t lcm(int64_t a, int64_t b) {
    return a * b / gcd(a, b);
}

int64_t lcm(vector<int> vec) {
    int64_t res = lcm(vec[0], vec[1]);
    for(int64_t i = 2; i < vec.size(); i++) {
        res = lcm(res, vec[i]);
    }
    return res;
}

int main() {
    ifstream file("input.txt");
    string line;
    string instructions;
    getline(file, instructions);
    getline(file, line); // skip line
    
    map<string, pair<string, string>> network;
    vector<string> cur;

    while(getline(file, line)) {
        network[line.substr(0, 3)] = make_pair(line.substr(7, 3), line.substr(12, 3));
        if(line[2] == 'A') {
            cur.push_back(line.substr(0, 3));
        }
    }
    
    int instructionPointer = 0;
    int steps = 0;
    vector<int> stepsFrom(cur.size(), 0);
    bool done = false;
    while(!done) {
        steps++;
        instructionPointer %= instructions.length();
        done = true;
        for(int i = 0; i < cur.size(); i++) {
            cur[i] = instructions[instructionPointer] == 'R' ? network[cur[i]].second : network[cur[i]].first;
            if(cur[i][2] == 'Z' && stepsFrom[i] == 0) {
                stepsFrom[i] = steps;
            }
            if(stepsFrom[i] == 0) {
                done = false;
            }
        }
        instructionPointer++;
    }
    
    cout << lcm(stepsFrom) << endl;
    return 0;
}