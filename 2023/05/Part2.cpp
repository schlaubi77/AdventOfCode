#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <queue>

using namespace std;

struct Range {
    int64_t begin; // inclusive
    int64_t end; // exclusive

    Range(int64_t beg, int64_t e) : begin(beg), end(e) {}
};

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

        vector<Range> applyOnRange(Range range) {
            vector<Range> working;
            working.push_back(range);
            vector<Range> done;
            for(int i = 0; i < length; i++) {
                vector<Range> newWorking;
                for(int j = 0; j < working.size(); j++) {
                    Range cur = working[j];
                    if(cur.begin > endings[i] || cur.end <= beginings[i]) {
                        newWorking.push_back(cur);
                        continue;
                    }
                    // ERR: i forgot to do >=, and did >
                    if(cur.begin >= beginings[i]) {
                        if(cur.end < endings[i]) {
                            done.push_back(Range(cur.begin + offsets[i], cur.end + offsets[i]));
                        } else {
                            done.push_back(Range(cur.begin + offsets[i], endings[i] + offsets[i]));
                            newWorking.push_back(Range(endings[i], cur.end));
                        }
                    } else {
                        newWorking.push_back(Range(cur.begin, beginings[i]));
                        if(cur.end < endings[i]) {
                            done.push_back(Range(beginings[i] + offsets[i], cur.end + offsets[i]));
                        } else {
                            done.push_back(Range(beginings[i] + offsets[i], endings[i] + offsets[i]));
                            newWorking.push_back(Range(endings[i], cur.end));
                        }
                    }
                }
                working = newWorking;
            }
            for(int i = 0; i < working.size(); i++) {
                done.push_back(working[i]);
            }
            return done;
        }

        vector<Range> applyOnRanges(vector<Range> ranges) {
            vector<Range> newRanges;
            for(int i = 0; i < ranges.size(); i++) {
                vector<Range> step = applyOnRange(ranges[i]);
                for(int j = 0; j < step.size(); j++) {
                    newRanges.push_back(step[j]);
                }
            }
            return newRanges;
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
    Range t = Range(5, 4);
    IntervalExchanger ex;

    ifstream file("input.txt");
    string line;
    getline(file, line);
    vector<int64_t> seedsNums = readNumbers(line);
    vector<Range> seeds;
    for(int i = 0; i < seedsNums.size(); i += 2) {
        seeds.push_back(Range(seedsNums[i], seedsNums[i] + seedsNums[i + 1]));
    }

    while (getline(file, line)) {
        if(line.length() == 0) {
            getline(file, line); // skip line
            // apply transformation, ERR: Why did Ii put this into for loop?
            seeds = ex.applyOnRanges(seeds);
            for(int i = 0; i < seeds.size(); i++) {
                cout << i << ": " << seeds[i].begin << ".." << seeds[i].end << endl;
            }
            ex = IntervalExchanger();
        } else {
            vector<int64_t> values = readNumbers(line);
            ex.add(values[1], values[1] + values[2], values[0] - values[1]);
        }
    }
    // apply last transformation and find min
    seeds = ex.applyOnRanges(seeds);
    int64_t min = seeds[0].begin;
    for(int i = 1; i < seeds.size(); i++) {
        if(seeds[i].begin < min) {
            min = seeds[i].begin;
        }
    }
    cout << min << endl;
}