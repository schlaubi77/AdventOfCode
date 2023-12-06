#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

class IntervalExchanger {
    private:
        vector<int64_t> beginings; // inclusive
        vector<int64_t> endings; // exclusive
        vector<int64_t> offsets;
        int length;

    public:
        IntervalExchanger() {
            length = 0;
        }
        void add(int64_t beg, int64_t end, int64_t offset) {
            beginings.push_back(beg);
            endings.push_back(end);
            offsets.push_back(offset);
            length++;
        }

        int64_t apply(int64_t val) {
            for(int i = 0; i < length; i++) {
                if(val >= beginings[i] && val < endings[i]) {
                    return val + offsets[i];
                }
            }
            return val;
        }
};

vector<int64_t> readNumbers(string s) {
    vector<int64_t> nums;
    int64_t cur = 0;
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
    IntervalExchanger ex;

    ifstream file("input.txt");
    string line;
    getline(file, line);
    vector<int64_t> seeds = readNumbers(line);
    
    while (getline(file, line)) {
        if(line.length() == 0) {
            getline(file, line); // skip line
            for(int i = 0; i < seeds.size(); i++) {
                seeds[i] = ex.apply(seeds[i]);
            }
            ex = IntervalExchanger();
        } else {
            vector<int64_t> values = readNumbers(line);
            ex.add(values[1], values[1] + values[2], values[0] - values[1]);
        }
    }
    // apply last transformation and find min
    int64_t min = ex.apply(seeds[0]);
    for(int i = 1; i < seeds.size(); i++) {
        int64_t applied = ex.apply(seeds[i]);
        if(applied < min) {
            min = applied;
        }
    }
    cout << min << endl;
}