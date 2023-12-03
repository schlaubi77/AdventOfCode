#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

using namespace std;

vector<string> readFile() {
    vector<string> lines;
    ifstream file("input.txt");
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

bool aroundSymbol(vector<string> lines, int i, int j) {
    for(int testI = max(0, i - 1); testI < min(int(lines.size()), i + 2); testI++) {
        for(int testJ = max(0, j - 1); testJ < min(int(lines[0].length()), j + 2); testJ++) {
            if(lines[testI][testJ] != '.' && !isdigit(lines[testI][testJ])) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int sum = 0;
    vector<string> lines = readFile();
    for(int i = 0; i < lines.size(); i++) {
        int currentNumber = 0;
        bool numberValid = false; // is adjacent
        for(int j = 0; j < lines[0].length(); j++) {
            if(isdigit(lines[i][j])) {
                currentNumber *= 10;
                currentNumber += lines[i][j] - '0';
                numberValid = numberValid || aroundSymbol(lines, i, j);
            } else {
                if(numberValid) {
                    sum += currentNumber;
                }
                currentNumber = 0;
                numberValid = false;
            }
        }
        // if valid number at end of line
        if(numberValid) {
            sum += currentNumber;
        }
    }
    cout << sum << endl;
    return 0;
}