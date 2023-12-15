#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>

#define MAP_SIZE 256

using namespace std;

int hash_algorithm(string s) {
    int hash = 0;
    for(int i = 0; i < s.length(); i++) {
        hash += s[i];
        hash *= 17;
        hash %= 256;
    }
    return hash;
}

vector<string> readFile() {
    fstream file("input.txt");
    string line;
    getline(file, line);
    stringstream stream(line);

    vector<string> instructions;
    while(getline(stream, line, ',')) {
        instructions.push_back(line);
    }
    return instructions;
}

void applyAction(vector<list<pair<string, int>>>& map, string action) {
    string key;
    int lens = 0;
    bool remove;
    for(int i = 0; i < action.length(); i++) {
        if(action[i] == '-' || action[i] == '=') {
            key = action.substr(0, i);
            remove = action[i] == '-';
            if(!remove) {
                lens = stoi(action.substr(i + 1));
            }
            break;
        }
    }
    int hash = hash_algorithm(key);
    if(remove) {
        for(list<pair<string, int>>::iterator it = map[hash].begin(); it != map[hash].end(); ++it) {
            pair<string, int> p = *it;
            if(p.first == key) {
                map[hash].erase(it);
                return;
            }
        }
    } else {
        for(list<pair<string, int>>::iterator it = map[hash].begin(); it != map[hash].end(); ++it) {
            pair<string, int> p = *it;
            if(p.first == key) {
                p.second = lens;
                *it = p;
                return;
            }
        }
        map[hash].push_back(make_pair(key, lens));
    } 
}

int main() {
    vector<string> instructions = readFile();
    vector<list<pair<string, int>>> map(MAP_SIZE); // vector of lists containing the entries (string -> int)
    for(string instruct : instructions) {
        applyAction(map, instruct);
    }
    int power = 0;
    int boxNum = 1;
    for(auto& box : map) {
        int pos = 1;
        for(auto& lens : box) {
            power += boxNum * pos * lens.second;
            pos++;
        }
        boxNum++;
    }
    cout << power;
}