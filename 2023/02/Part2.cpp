#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int findMaxNeeded(string s, string color) {
    int maxNeeded = 0;
    while(s.find(color) != string::npos) {
        int pos = s.find(color);
        maxNeeded = max(maxNeeded, stoi(s.substr(pos - 3, 2)));
        s.replace(pos, color.length(), "");
    }
    return maxNeeded;
}

int main()
{
    ifstream file("input.txt");
    string line;
    int res = 0;
    while (getline(file, line)) {
        res += findMaxNeeded(line, "red") * findMaxNeeded(line, "green") * findMaxNeeded(line, "blue");
    }
    cout << res << endl;
    return 0;
}