#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#define N_CARDS 198

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
    int wins[N_CARDS];
    int total = 0;
    for(int j = 0; j < lines.size(); j++) {
        string line = lines[j];
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
                score++;
            }
        }
        wins[j] = score;
    }
    int stock[N_CARDS] = {0};
    cout << stock[45] << endl;
    for(int i = 0; i < lines.size(); i++) {
        stock[i]++;
        for(int j = 1; j <= wins[i]; j++) {
            if(i + j < N_CARDS) {
                stock[i + j] += stock[i];
            } 
        }
        total += stock[i];
    }
    cout << total << endl;
    return 0;
}