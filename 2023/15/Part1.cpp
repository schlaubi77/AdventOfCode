#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int hash_algorithm(string s) {
    int hash = 0;
    for(int i = 0; i < s.length(); i++) {
        hash += s[i];
        hash *= 17;
        hash %= 256;
    }
    return hash;
}

int main() {
    fstream file("input.txt");
    string line;
    getline(file, line);
    stringstream stream(line);
    int sum = 0;
    while(getline(stream, line, ',')) {
        sum += hash_algorithm(line);
    }
    cout << sum << endl;
}