#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <algorithm>

#define INPUT_LENGTH 2145

using namespace std;


bool contains(int ar[INPUT_LENGTH][3], int contained[3]) {
    bool isNeighbour = false;
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
    int cubeOutside[3];
    string line;

    int surfaces = 0;

    while (getline(file, line)) {
        int comma1 = line.find(',');
        int comma2 = line.substr(comma1 + 1, string::npos).find(',') + comma1 + 1;

        cubes[index][0] = stoi(line.substr(0, comma1));
        cubes[index][1] = stoi(line.substr(comma1 + 1, comma2));
        cubes[index][2] = stoi(line.substr(comma2 + 1));

        if (cubes[index][0] + 1 > cubeOutside[0]) {
            cubeOutside[0] = cubes[index][0] + 1;
        }
        if (cubes[index][1] + 1 > cubeOutside[1]) {
            cubeOutside[1] = cubes[index][1] + 1;
        }
        if (cubes[index][2] + 1 > cubeOutside[2]) {
            cubeOutside[2] = cubes[index][2] + 1;
        }

        // add surfaces of cubes witch are on the edge of the cubes bounding box
        if (cubes[index][0] == 0 || cubes[index][1] == 0 || cubes[index][2] == 0) {
            surfaces++;
        }
        index++;
    }

    
    
    // BFS all the cubes outside the cube and check if they are neighbour

    // position of cubes to search where pos0 * 256 * 256 + pos1 * 256 + pos2
    queue<int> stack;

    // position of searched cubes where pos0 * 256 * 256 + pos1 * 256 + pos2
    list<int> wasSearched;

    stack.push(cubeOutside[0] * 65536 + cubeOutside[1] * 256 + cubeOutside[2]);

    wasSearched.push_back(cubeOutside[0] * 65536 + cubeOutside[1] * 256 + cubeOutside[2]);
    

    while (!stack.empty()) {
        int currentCube[3] = {stack.front() / 65536, (stack.front() % 65536) / 256, stack.front() % 256};
        for (int axis = 0; axis < 3; axis++) {
            for (int offset = -1; offset <= 1; offset += 2) {
                int copy[3];
                for (int ii = 0; ii < 3; ii++) {
                    copy[ii] = currentCube[ii];
                }
                copy[axis] += offset;
                if (find(wasSearched.begin(), wasSearched.end(), copy[0] * 65536 + copy[1] * 256 + copy[2]) == wasSearched.end() && copy[0] <= cubeOutside[0] && copy[0] >= 0 && copy[1] <= cubeOutside[1] && copy[1] >= 0 && copy[2] <= cubeOutside[2] && copy[2] >= 0) {
                    if (!contains(cubes, copy)) {
                        stack.push(copy[0] * 65536 + copy[1] * 256 + copy[2]);
                        wasSearched.push_back(copy[0] * 65536 + copy[1] * 256 + copy[2]);
                    }
                } 
            }
        }
        stack.pop();
    }
    // check for each cube in the bounding box
    for (int i = 0; i < cubeOutside[0]; i++) {
        for (int j = 0; j < cubeOutside[1]; j++) {
            for (int k = 0; k < cubeOutside[2]; k++) {
                // which is within the lava sphere
                if (find(wasSearched.begin(), wasSearched.end(), i * 65536 + j * 256 + k) == wasSearched.end()) {
                    // for each surface
                    for (int axis = 0; axis < 3; axis++) {
                        for (int offset = -1; offset <= 1; offset += 2) {
                            int cubeToCheck[3] = {i, j, k};
                            cubeToCheck[axis] += offset;
                            // if the surface touches the outside
                            if (find(wasSearched.begin(), wasSearched.end(), cubeToCheck[0] * 65536 + cubeToCheck[1] * 256 + cubeToCheck[2]) != wasSearched.end()) {
                                surfaces++;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << surfaces;
}