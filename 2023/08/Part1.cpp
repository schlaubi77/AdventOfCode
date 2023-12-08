#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    ifstream file("input.txt");
    string line;
    string instructions;
    getline(file, instructions);
    getline(file, line); // skip line
    map<string, pair<string, string>> network;
    while(getline(file, line)) {
        network[line.substr(0, 3)] = make_pair(line.substr(7, 3), line.substr(12, 3));
    }

    string cur = "AAA";
    int instructionPointer = 0;
    int steps = 0;
    while(cur != "ZZZ") {
        steps++;
        instructionPointer %= instructions.length();
        cur = instructions[instructionPointer] == 'R' ? network[cur].second : network[cur].first;
        instructionPointer++;
    }
    cout << steps << endl;
    return 0;
}