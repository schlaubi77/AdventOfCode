#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<string> readFile() {
    vector<string> lines;
    ifstream file("input.txt");
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main() {
    vector<string> lines = readFile();
    int sum = 0;
    for(string line : lines) {
        set<int> winning;
        for(int i = 42; i < line.length(); i += 3) {
            int num = isdigit(line[i]) ? (line[i] - '0') * 10 : 0;
            num += line[i + 1] - '0';
            winning.insert(num);
        }
        int score = 0;
        for(int i = 10; i < 40; i += 3) {
            int num = isdigit(line[i]) ? (line[i] - '0') * 10 : 0;
            num += line[i + 1] - '0';
            if(winning.find(num) != winning.end()) {
                if(score == 0) {
                    score = 1;
                } else {
                    score *= 2;
                }
            }
        }
        sum += score;
    }
    cout << sum << endl;
    return 0;
}