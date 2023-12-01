#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream file("input.txt");
    string line;
    int sum = 0;

    while (getline(file, line)) {
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