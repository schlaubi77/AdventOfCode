#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

        row.push_back(make_pair(line.substr(0, line.find(" ")), nums));
    }
    return row;
}

int findConfigurations(string cfg, vector<int> nums) {
    if(cfg.length() == 0) {
        return nums.size() == 0;
    }
    if(nums.size() == 0) {
        return cfg.find('#') == string::npos;
    }
    int res = 0;
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
    return res;
}

int main() {
    vector<pair<string, vector<int>>> rows = readFile();
    int totalCfgs = 0;
    for(int i = 0; i < rows.size(); i++) {
        totalCfgs += findConfigurations(rows[i].first, rows[i].second);
    }
    cout << totalCfgs << endl;
}