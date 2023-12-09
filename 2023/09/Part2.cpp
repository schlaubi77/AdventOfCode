#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int prevValue(vector<int> seq) {
    bool isZero = seq[0] == 0;
    vector<int> differences;
    for(int i = 1; i < seq.size(); i++) {
        if(seq[i] != 0) {
            isZero = false;
        }
        differences.push_back(seq[i] - seq[i - 1]);
    }
    if(isZero) {
        return 0;
    }
    return seq[0] - prevValue(differences);
}

vector<int> readNumbers(string s) {
    vector<int> vec;
    istringstream iss(s);
    int i = 0;
    while(iss >> i) {
        vec.push_back(i);
    }
    return vec;
}

int main() {
    ifstream file("input.txt");
    string line;
    int sum = 0;
    while(getline(file, line)) {
        sum += prevValue(readNumbers(line));
    }
    cout << sum << endl;
    
}