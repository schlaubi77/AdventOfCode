#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> readNumbers(string s) {
    vector<int> nums;
    int cur = 0;
    bool found = false;
    for(int i = 0; i < s.length(); i++) {
        if(isdigit(s[i])) {
            cur *= 10;
            cur += s[i] - '0';
            found = true;
        } else if(found) {
            nums.push_back(cur);
            cur = 0;
            found = false;
        }
    }
    // add last number
    if(found) {
        nums.push_back(cur);
        cur = 0;
        found = false;
    }
    return nums;
}

int main() {
    ifstream file("input.txt");
    string line;
    getline(file, line);
    vector<int> times = readNumbers(line);
    getline(file, line);
    vector<int> records = readNumbers(line);
    int product = 1;
    for(int i = 0; i < times.size(); i++) {
        for(int t = 0; i < times[i]; t++) {
            if(t * (times[i] - t) > records[i]) {
                product *= times[i] - 2 * t + 1;
                break;
            }
        }
    }
    cout << product << endl;
}