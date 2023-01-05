#include <iostream>
#include <fstream>
#include <string>
#define INPUT_LENGTH 2145

using namespace std;

bool contain(int ar[INPUT_LENGTH][3], int contained[3]) {
    for (int i = 0; i < INPUT_LENGTH; i++) {
        if (ar[i][0] == contained[0] && ar[i][1] == contained[1] && ar[i][2] == contained[2]) {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream file("input.txt");
    int cubes[INPUT_LENGTH][3];
    int index = 0;
    string line;

    while (getline(file, line)) {
        int comma1 = line.find(',');
        int comma2 = line.substr(comma1 + 1, string::npos).find(',') + comma1 + 1;

        cubes[index][0] = stoi(line.substr(0, comma1));
        cubes[index][1] = stoi(line.substr(comma1 + 1, comma2));
        cubes[index][2] = stoi(line.substr(comma2 + 1));

        index++;
    }
    
    int surfaces = 0;

    for (int i = 0; i < INPUT_LENGTH; i++) {
        for (int axis = 0; axis < 3; axis++) {
            for (int offset = -1; offset <= 1; offset += 2) {
                int copy[3];
                for (int ii = 0; ii < 3; ii++) {
                    copy[ii] = cubes[i][ii];
                }
                copy[axis] += offset;
                if (!contain(cubes, copy)) {
                    surfaces++;
                }
            }
        }
    }
    cout << surfaces;
    return 0;
}