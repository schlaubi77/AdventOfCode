#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdint.h>
#include <stdexcept>

using namespace std;

map<string, uint64_t> values;
map<string, string> variables;

uint64_t calculateNumber(string str) {
    if (str == "humn") {
        throw logic_error("humn");
    }

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
    }
}

uint64_t calculateReverse(string str, uint64_t parent) {
    cout << str << ": " << parent << endl;
    if (str == "humn") {
        return parent;
    }
    string job = variables[str];
    bool firstIsPathToHumn = false;
    uint64_t v;

    try {
        v = calculateNumber(job.substr(0, 4));
    }
    catch (exception ex) {
        firstIsPathToHumn = true;
        v = calculateNumber(job.substr(7, 4));
    }

    uint64_t thisMonkeyVal;
    if (firstIsPathToHumn) {
        switch (job[5])
        {
        case '+':
            thisMonkeyVal = parent - v;
            break;
        case '-':
            thisMonkeyVal = parent + v;
            break;
        case '*':
            thisMonkeyVal = parent / v;
            break;
        case '/':
            thisMonkeyVal = parent * v;
            break;
        }
    }
    else {
        switch (job[5])
        {
        case '+':
            thisMonkeyVal = parent - v;
            break;
        case '-':
            thisMonkeyVal = v - parent;
            break;
        case '*':
            thisMonkeyVal = parent / v;
            break;
        case '/':
            thisMonkeyVal = v / parent;
            break;
        }
    }

    if (firstIsPathToHumn) {
        return calculateReverse(job.substr(0, 4), thisMonkeyVal);
    }
    else {
        return calculateReverse(job.substr(7, 4), thisMonkeyVal);
    }
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

    uint64_t target;
    bool searchFirstPath = false;
    try {
        target = calculateNumber(variables["root"].substr(0, 4));
    }
    catch (exception ex) {
        searchFirstPath = true;
        target = calculateNumber(variables["root"].substr(7, 4));
    }

    cout << target << endl;

    uint64_t r;
    if (searchFirstPath) {
        r = calculateReverse(variables["root"].substr(0, 4), target);
    }
    else {
        r = calculateReverse(variables["root"].substr(7, 4), target);
    }

    cout << r;

    return 0;
}