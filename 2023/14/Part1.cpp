#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readFile() {
    fstream file("input.txt");
    string line;
    vector<string> platform;
    while(getline(file, line)) {
        platform.push_back(line);
    }
    return platform;
}

int main() {
    vector<string> platform = readFile();
    int height = platform.size();
    int load = 0;
    for(int i = 0; i < platform[0].length(); i++) {
        int movePos = 0;
        for(int j = 0; j < height; j++) {
            if(platform[j][i] == 'O') {
                load += height - movePos;
                movePos++;
            } else if (platform[j][i] == '#') {
                movePos = j + 1;
            }
        }
    }
    cout << load << endl;
}