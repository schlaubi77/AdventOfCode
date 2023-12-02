#include <iostream>
#include <fstream>
#include <string>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

using namespace std;

int main()
{
    ifstream file("input.txt");
    string line;
    int res = 0;
    int id = 1;
    while (getline(file, line)) {
        bool valid = true;

        while(valid && line.find("red") != string::npos) {
            int pos = line.find("red");
            if(stoi(line.substr(pos - 3, 2)) > MAX_RED) {
                valid = false;
            }
            line.replace(pos, 3, "");
        }
        while(valid && line.find("green") != string::npos) {
            int pos = line.find("green");
            if(stoi(line.substr(pos - 3, 2)) > MAX_GREEN) {
                valid = false;
            }
            line.replace(pos, 5, "");
        }
        while(valid && line.find("blue") != string::npos) {
            int pos = line.find("blue");
            if(stoi(line.substr(pos - 3, 2)) > MAX_BLUE) {
                valid = false;
            }
            line.replace(pos, 4, "");
        }

        if(valid) {
            res += id;
        }
        id++;
    }
    cout << res << endl;
    return 0;
}