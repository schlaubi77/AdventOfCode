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

int readNumber(vector<string> lines, int i, int j) {
    int num = 0;
    for(int testJ = max(0, j - 2); testJ < min(int(lines[0].length()), j + 3); testJ++) {
        if(isdigit(lines[i][testJ])) {
            num *= 10;
            num += lines[i][testJ] - '0';
        } else if(testJ < j) {
            num = 0;
        } else {
            break;
        }
    }
    return num;
}

int findRatio(vector<string> lines, int i, int j) {
    int numCount = 0;
    int product = 1;
    for(int testI = max(0, i - 1); testI < min(int(lines.size()), i + 2); testI++) {
        if(j > 0 && isdigit(lines[testI][j - 1])) {
            if(!isdigit(lines[testI][j]) && j + 1 < lines[0].length() && isdigit(lines[testI][j + 1])) {
                //  1.1
                numCount += 2;
                product *= readNumber(lines, testI, j - 1);
                product *= readNumber(lines, testI, j + 1);
            } else {
                // 1..
                numCount++;
                product *= readNumber(lines, testI, j - 1);
            }
        } else if(isdigit(lines[testI][j])) {
            // .1.
            numCount++;
            product *= readNumber(lines, testI, j);
        } else if(j + 1 < lines[0].length() && isdigit(lines[testI][j + 1])) {
            // ..1
            numCount++;
            product *= readNumber(lines, testI, j + 1);
        }
    }
    return numCount == 2 ? product : 0;
}

int main()
{
    int sum = 0;
    vector<string> lines = readFile();
    for(int i = 0; i < lines.size(); i++) {
        for(int j = 0; j < lines[0].length(); j++) {
            if(lines[i][j] == '*') {
                sum += findRatio(lines, i, j);
            }
        }
    }
    cout << sum << endl;
    return 0;
}