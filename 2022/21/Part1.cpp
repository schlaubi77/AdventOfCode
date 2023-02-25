#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdint.h>

using namespace std;

map<string, uint64_t> values;
map<string, string> variables;

uint64_t calculateNumber(string str) {
    if (values.find(str) != values.end()) {
        return values[str];
    }
    string job = variables[str];
    uint64_t v0 = calculateNumber(job.substr(0, 4));
    uint64_t v1 = calculateNumber(job.substr(7, 4));

    switch (job[5])
    {
    case '+':
        return v0 + v1;
    case '-':
        return v0 - v1;
    case '*':
        return v0 * v1;
    case '/':
        return v0 / v1;
    default:
        cout << "################" << endl;
        break;
    }

    cout << "################" << endl;
    return 0;
}

int main()
{
    ifstream file("input.txt");
    string line;

    while (getline(file, line)) {
        if (line.length() == 17) {
            variables.insert(pair<string, string>(line.substr(0, 4), line.substr(6)));
        }
        else {
            values.insert(pair<string, uint64_t>(line.substr(0, 4), stoi(line.substr(6))));
        }
    }

    uint64_t r = calculateNumber("root");
    cout << r;

    return 0;
}