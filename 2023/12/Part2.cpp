#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <map>

using namespace std;

vector<pair<string, vector<int>>> readFile() {
    vector<pair<string, vector<int>>> row;
    ifstream file("input.txt");
    string line;
    while(getline(file, line)) {
        vector<int> nums;
        stringstream sStream(line.substr(line.find(" ") + 1));
        string n;
        while(getline(sStream, n, ',')) {
            nums.push_back(stoi(n));
        }
        int size = nums.size();
        for(int i = 0; i < size * 4; i++) {
            nums.push_back(nums[i]);
        }
        string l = line.substr(0, line.find(" "));
        row.push_back(make_pair(l + "?" + l + "?" + l + "?" + l + "?" + l, nums));
    }
    return row;
}

string makeKey(string cfg, vector<int> nums) {
    string key = cfg;
    for(int i = 0; i < nums.size(); i++) {
        key += to_string(nums[i]) + ",";
    }
    return key;
}

map<string, int64_t> cache;

int64_t findConfigurations(string cfg, vector<int> nums) {
    if(cfg.length() == 0) {
        return nums.size() == 0;
    }
    if(nums.size() == 0) {
        return cfg.find('#') == string::npos;
    }
    string key = makeKey(cfg, nums);
    if(cache.count(key)) {
        return cache[key];
    }
    int64_t res = 0;
    if(cfg[0] != '#') {
        res += findConfigurations(cfg.substr(1), nums);
    }
    if(cfg[0] != '.') {
        if(nums[0] < cfg.length() && (cfg.find('.') >= nums[0] || cfg.find('.') == string::npos) && cfg[nums[0]] != '#') {
            vector<int> newNums;
            for(int i = 1; i < nums.size(); i++) {
                newNums.push_back(nums[i]);
            }
            res += findConfigurations(cfg.substr(nums[0] + 1), newNums);
        } else if(nums[0] == cfg.length() && cfg.find('.') == string::npos) {
            vector<int> newNums;
            for(int i = 1; i < nums.size(); i++) {
                newNums.push_back(nums[i]);
            }
            res += findConfigurations("", newNums);
        }
    }
    cache[key] = res;
    return res;
}

int main() {
    vector<pair<string, vector<int>>> rows = readFile();
    int64_t totalCfgs = 0;
    for(int i = 0; i < rows.size(); i++) {
        totalCfgs += findConfigurations(rows[i].first, rows[i].second);
    }
    cout << totalCfgs << endl;
    return 0;
}