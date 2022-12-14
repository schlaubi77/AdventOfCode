#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool containsDuplicate(string s) {
    for(int i = 0; i < s.length(); i++) {
        for(int i2 = 0; i2 < s.length(); i2++) {
            if(i != i2 && s[i] == s[i2]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ifstream file("input.txt");
    string lastFour = "";
    int position = 0;
    while(file) {
        position++;
        char c;
        file.get(c);
        if(position <= 14) {
            lastFour += c;
            continue;
        } else {
            lastFour = lastFour.substr(1, 13) + c;
        }
        if(!containsDuplicate(lastFour)) {
            cout << position << lastFour;
            return 0;
        }
    }
    return 0;
}
