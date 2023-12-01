#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string numberWords[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

void wordtoNumber(string &s) {
    for (int j = 0; j < s.length() - 2; j++) {
        for (int i = 0; i < 9; i++) {
            while (s.find(numberWords[i]) == j) {
                // -1 to handle cases like eighthree => 83
                s.replace(s.find(numberWords[i]), numberWords[i].length() - 1, to_string(i + 1));
            }
        }
    }
}

int main()
{
    ifstream file("input.txt");
    string line;
    int sum = 0;

    while (getline(file, line)) {
        wordtoNumber(line);
        cout << line << endl;
        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                sum += 10 * (line[i] - 48);
                break;
            }
        }
        for (int i = line.length() - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                sum += line[i] - 48;
                break;
            }
        }
    }

    cout << sum << endl;

    return 0;
}