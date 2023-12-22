#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdint>

using namespace std;

struct Workflow;

map<string, Workflow> list;
map<char, int> typeToIdx = {{'x', 0}, {'m', 1}, {'a', 2}, {'s', 3}};

struct Range {
    int mins[4];
    int maxes[4];

    int64_t product() {
        int64_t prod = 1;
        for(int i = 0; i < 4; i++) {
            prod *= maxes[i] - mins[i] + 1;
        }
        return prod;
    }

    bool valid() {
        for(int i = 0; i < 4; i++) {
            if(maxes[i] < mins[i]) {
                return false;
            }
        }
        return true;
    }
};

struct Workflow {
    vector<char> ratingType;
    vector<int> threshold;
    vector<bool> higher; // else lower
    vector<string> success;
    string fail;
    
    int64_t forward(Range r) {
        return forward(r, 0);
    }

    int64_t forward(Range r, int i) {
        if(i >= success.size()) {
            if(fail.length() == 1) {
                if(fail == "A") {
                    return r.product();
                } else {
                    return 0;
                }
            } else {
                return list[fail].forward(r);
            }
        }
        int64_t options = 0;
        Range fulfilled(r);
        Range failed(r);

        int typeIdx = typeToIdx[ratingType[i]];

        if(higher[i]) {
            fulfilled.mins[typeIdx] = threshold[i] + 1;
            failed.maxes[typeIdx] = threshold[i];
        } else {
            fulfilled.maxes[typeIdx] = threshold[i] - 1;
            failed.mins[typeIdx] = threshold[i];
        }

        if(fulfilled.valid()) {
            if(success[i].length() == 1) {
                if(success[i] == "A") {
                    options += fulfilled.product();
                }
            } else {
                options += list[success[i]].forward(fulfilled);
            }
        }

        if(failed.valid()) {
            options += forward(failed, i + 1);
        }
        return options;
    }
};

void readList(fstream& stream) {
    string line;
    while(getline(stream, line)) {
        if(line.length() == 0) {
            break;
        }
        string name = line.substr(0, line.find("{"));
        stringstream sstream(line.substr(line.find("{") + 1));
        string l2;

        vector<char> ratingType;
        vector<int> threshold;
        vector<bool> higher;
        vector<string> success;

        while(getline(sstream, l2, ',')) {
            if(l2.length() <= 5) {
                list[name] = Workflow({ratingType, threshold, higher, success, l2.substr(0, l2.find("}"))});
                break;
            }
            ratingType.push_back(l2[0]);
            higher.push_back(l2[1] == '>');
            threshold.push_back(stoi(l2.substr(2, l2.find(":") - 2)));
            success.push_back(l2.substr(l2.find(":") + 1));
        }
    }
}

int main() {
    fstream file("input.txt");
    readList(file);
    // OH MY GOD I put 0 instead of 1
    Range test({{1, 1, 1, 1}, {4000, 4000, 4000, 4000}});

    cout << list["in"].forward(test) << endl;
}

