#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

struct Workflow;

map<string, Workflow> list;

struct Part {
    int x, m, a, s;
    Part(int in[4]) {
        x = in[0];
        m = in[1];
        a = in[2];
        s = in[3];
    }
};

struct Workflow {
    vector<char> ratingType;
    vector<int> threshold;
    vector<bool> higher; // else lower
    vector<string> success;
    string fail;
    
    bool forward(Part p) {
        for(int i = 0; i < ratingType.size(); i++) {
            int val;
            switch(ratingType[i]) {
            case 'x':
                val = p.x;
                break;
            case 'm':
                val = p.m;
                break;
            case 'a':
                val = p.a;
                break;
            case 's':
                val = p.s;
                break;
            }
            if((val > threshold[i] && higher[i]) || (val < threshold[i] && !higher[i])) {
                if(success[i].length() == 1) {
                    return success[i][0] == 'A';
                } else {
                    return list[success[i]].forward(p);
                }
            }
        }
        if(fail.length() == 1) {
            return fail[0] == 'A';
        } else {
            return list[fail].forward(p);
        }
    }
};

void readList(fstream& stream) {
    string line;
    while(getline(stream, line)) {
        if(line.length() == 0) {
            break;
        }
        string name = line.substr(0, line.find("{"));
        stringstream sstream(line.substr(line.find("{") + 1));
        string l2;

        vector<char> ratingType;
        vector<int> threshold;
        vector<bool> higher;
        vector<string> success;

        while(getline(sstream, l2, ',')) {
            if(l2.length() <= 5) {
                list[name] = Workflow({ratingType, threshold, higher, success, l2.substr(0, l2.find("}"))});
                break;
            }
            ratingType.push_back(l2[0]);
            higher.push_back(l2[1] == '>');
            threshold.push_back(stoi(l2.substr(2, l2.find(":") - 2)));
            success.push_back(l2.substr(l2.find(":") + 1));
        }
    }
}

vector<Part> readParts(fstream& stream) {
    vector<Part> parts;
    string line;
    while(getline(stream, line)) {
        stringstream sstream(line.substr(1, line.length() - 2));
        string l2;
        int partVals[4];
        int i = 0;
        while(getline(sstream, l2, ',')) {
            partVals[i] = stoi(l2.substr(2));
            i++;
        }
        parts.push_back(Part(partVals));
    }
    return parts;
}

int main() {
    fstream file("input.txt");
    readList(file);
    vector<Part> parts = readParts(file);
    
    int sum = 0;
    for(Part p : parts) {
        if(list["in"].forward(p)) {
            sum += p.x + p.m + p.a + p.s;
        }
    }
    cout << sum << endl;
}

