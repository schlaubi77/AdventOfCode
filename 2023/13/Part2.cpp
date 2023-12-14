#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool columnEquals(vector<string> vec, int a, int b) {
    for(int i = 0; i < vec.size(); i++) {
        if(vec[i][a] != vec[i][b]) {
            return false;
        }
    }
    return true;
}

bool columnOneDifference(vector<string> vec, int a, int b) {
    bool differenceFound = false;
    for(int i = 0; i < vec.size(); i++) {
        if(vec[i][a] != vec[i][b]) {
            if(differenceFound) {
                return false;
            }
            differenceFound = true;
        }
    }
    return differenceFound;
}

bool rowOneDifference(vector<string> vec, int a, int b) {
    if(vec[a] == vec[b]) {
        return false;
    }
    bool differenceFound = false;
    for(int i = 0; i < vec[a].length(); i++) {
        if(vec[a][i] != vec[b][i]) {
            if(differenceFound) {
                return false;
            }
            differenceFound = true;
        }
    }
    return differenceFound;
}

int findReflectionVal(vector<string> vec) {
    for(int i = 0; i < vec.size() - 1; i++) {
        if(vec[i] == vec[i + 1] || rowOneDifference(vec, i, i + 1)) {
            bool differenceFound = rowOneDifference(vec, i, i + 1);
            for(int j = 1; i - j >= 0 && i + 1 + j < vec.size(); j++) {
                if(vec[i - j] == vec[i + 1 + j]) {
                } else if(rowOneDifference(vec, i - j, i + 1 + j) && !differenceFound) {
                    differenceFound = true;
                } else {
                    goto continueOuter;
                }
            }
            if(differenceFound) {
                return 100 * (i + 1);
            }
        }
        continueOuter:;
    }
    for(int i = 0; i < vec[0].length() - 1; i++) {
        if(columnEquals(vec, i, i + 1) || columnOneDifference(vec, i, i + 1)) {
            bool differenceFound = columnOneDifference(vec, i, i + 1);
            for(int j = 1; i - j >= 0 && i + 1 + j < vec[0].length(); j++) {
                if(columnEquals(vec, i - j, i + 1 + j)) {
                } else if(columnOneDifference(vec, i - j, i + 1 + j) && !differenceFound) {
                    differenceFound = true;
                } else {
                    goto continueOuter2;
                }
            }
            if(differenceFound) {
                return i + 1;
            }
        }
        continueOuter2:;
    }
    cout << "NO REFLECTION FOUND" << endl;
    return 0;
}

int main() {
    fstream file("input.txt");
    string line;
    vector<string> pattern;
    int sum = 0;
    int i = 0;
    while(getline(file, line)) {
        if(line.length() == 0) {
            sum += findReflectionVal(pattern);
            pattern = vector<string>();
        } else {
            pattern.push_back(line);
        }
    }
    sum += findReflectionVal(pattern);
    cout << sum << endl;
}
