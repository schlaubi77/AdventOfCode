#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

uint64_t readNumber(string s) {
    uint64_t num = 0;
    bool found = false;
    for(uint64_t i = 0; i < s.length(); i++) {
        if(isdigit(s[i])) {
            num *= 10;
            num += s[i] - '0';
        } 
    }
    return num;
}

int main() {
    ifstream file("input.txt");
    string line;
    getline(file, line);
    uint64_t time = readNumber(line);
    getline(file, line);
    uint64_t record = readNumber(line);
    uint64_t res = 0;
    for(uint64_t t = 0; t < time; t++) {
        if(t * (time - t) > record) {
            res = time - 2 * t + 1;
            break;
        }
    }
    cout << res << endl;
}